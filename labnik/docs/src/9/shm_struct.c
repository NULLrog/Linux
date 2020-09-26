#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LEN 255
struct message{
	pid_t pid;
	char text[MAX_LEN];
};

int main(int argc, const char *argv[]){
    
    int shmid;
    struct message mes, *shm, *s;
    
    if (argc < 2 || strlen(argv[1])>MAX_LEN){
		fprintf (stderr, "Используйте %s \"сообщение maxlen=%d\"\n", argv[0], MAX_LEN);
		exit (1);
	}
	strcpy(mes.text, argv[1]);
	mes.pid = getpid();
    int size = sizeof(mes);
    /* Создадим область разделяемой памяти */
    if ((shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /* Получим доступ к разделяемой памяти */
    if ((shm = shmat(shmid, NULL, 0)) == (struct message *) -1) {
        perror("shmat");
        exit(1);
    }

    /* Запишем в разделяемую память */
	s = shm;
	*s = mes;
	pid_t pid;
	pid = fork();
	if (0 == pid) {

		/* Прочитаем из разделяемой памяти */
		s = shm;
		printf("%s pid=%d", s->text, s->pid);	
		
		if (shmdt(shm) < 0) {
			printf("Ошибка отключения\n");
			exit(1);
		} 
		exit(0);
		
	} else if (pid < 0){
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	}	
	
	wait(NULL);
	
	/* Удалим созданные объекты IPC */	
	 if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	}
    exit(0);
}
