/*4. Warcraft. Заданное количество юнитов добывают золото 
* равными порциями из одной шахты, задерживаясь в пути 
* на случайное время, до ее истощения. Работа каждого юнита 
* реализуется в порожденном процессе.*/
#include <wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include "warcraft.h"

#define MINE 10

int msgqid;

void send_message(int qid, struct mymsgbuf *qbuf, int num) {
    qbuf->mtype = 1;
    qbuf->number = num;
    if((msgsnd(qid, (struct msgbuf *)qbuf, 1, IPC_NOWAIT))==-1) {
        perror("Ошибка создания единицы сырья!");
        exit(1);
    }
}

void read_message(int qid, struct mymsgbuf *qbuf) {
	sleep(rand() % 4);
    msgrcv(qid, (struct msgbuf *)qbuf, 1, 0, IPC_NOWAIT);
    printf("ЮНИТ: %d завершил добычу в шахте!\n", qbuf->number);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    int pid[atoi(argv[1])], status, stat;
    key_t key;
    struct mymsgbuf qbuf;
    struct msqid_ds info;
    if (argc < 2) {
        printf("Введите количество юнитов!\n");
        exit(-1);
    }

    key = ftok("Makefile", 'm');
    if(!(msgqid = msgget(key, IPC_CREAT|0660))) {
        perror("Не удалось создать очередь сообщений");
        exit(-2);
    }
    printf("ШАХТА: Создание %d единиц сырья!\n", MINE);
    fflush(stdout);
    for (int i = 0; i < MINE; i++)
        send_message(msgqid, (struct mymsgbuf *)&qbuf, i+1);

    for (int i = 0; i < atoi(argv[1]); i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            perror("Ошибка создания юнита");
            exit(-3);
        } else if (pid[i] == 0) {
            printf("ЮНИТ: Это %d процесс-юнит СТАРТ!\n", i+1);
            fflush(stdout);
            sleep(rand() % 4);
            printf("ЮНИТ: Это %d процесс-юнит ВЫХОД!\n", i+1);
            fflush(stdout);
            read_message(msgqid, &qbuf);
            fflush(stdout);
            exit(0);
        }
    }

    for (int i = 0; i < atoi(argv[1]); i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("Процесс-юнит %d завершился, result=%d\n", i+1, WEXITSTATUS(stat));
            fflush(stdout);
        }
    }
    msgctl(msgqid, IPC_STAT, &info);
    if(info.msg_qnum == 0) {
        if ((msgctl(msgqid, IPC_RMID, NULL)) == -1) {
            perror("Не удалось удалить очередь сообщений!");
            exit(-4);
        }
        else
			printf("Очередь была удалена!");
    }
    else
		printf("В очереди осталось %ld сообщений!\n", info.msg_qnum);
    return 0;
}
