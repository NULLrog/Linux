#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf {
        long mtype;
        char mtext[MAX_SEND_SIZE];
};

int msgqid, rc;

void send_message(int qid, struct mymsgbuf *qbuf, long type, char *text){
        qbuf->mtype = type;
        strcpy(qbuf->mtext, text);

        if((msgsnd(qid, (struct msgbuf *)qbuf,
                strlen(qbuf->mtext)+1, 0)) ==-1){
                perror("msgsnd");
                exit(1);
        }
}

void read_message(int qid, struct mymsgbuf *qbuf, long type){
        qbuf->mtype = type;
        msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
        printf("Type: %ld Text: %s\n", qbuf->mtype, qbuf->mtext);
}

int main(int argc, char *argv[]) {
    int i, pid[argc], status, stat;
    key_t key;
    int qtype = 1;
    struct mymsgbuf qbuf;
    
    if (argc < 2) {
        printf("Usage: ./fork_many text text ...\n");
        exit(-1);
    }
    
    key = ftok(".", 'm');
	if((msgqid = msgget(key, IPC_CREAT|0660)) == -1) {
		perror("msgget");
		exit(1);
	}
        
    for (i = 1; i < argc; i++) {
        // запускаем дочерний процесс 
        pid[i] = fork();
        srand(getpid());

        if (-1 == pid[i]) {
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        } else if (0 == pid[i]) {
            printf(" CHILD: Это %d процесс-потомок СТАРТ!\n", i);
            sleep(rand() % 4);
            printf(" CHILD: Это %d процесс-потомок ВЫХОД!\n", i);
            
            char str[10];
            sprintf(str, "%d", (int)strlen(argv[i]));
            send_message(msgqid, (struct mymsgbuf *)&qbuf,
                                       qtype, str); 
			printf(" CHILD: Это %d процесс-потомок отправил сообщение!\n", i);
			fflush(stdout);
            exit(0); /* выход из процесс-потомока */
        }
    }
    // если выполняется родительский процесс
    printf("PARENT: Это процесс-родитель!\n");
    // ожидание окончания выполнения всех запущенных процессов
    for (i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("процесс-потомок %d done,  result=%d text=%s\n", i, WEXITSTATUS(stat), argv[i]);
            fflush(stdout);
        }
    }

    for (i = 1; i < argc; i++) {
		        read_message(msgqid, &qbuf, qtype); 
	}
	
	if ((rc = msgctl(msgqid, IPC_RMID, NULL)) < 0) {
		perror( strerror(errno) );
		printf("msgctl (return queue) failed, rc=%d\n", rc);
		return 1;
	}
    return 0;
}
