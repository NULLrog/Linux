#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, const char *argv[]){
    
    int *shm, *s, shmid, count = 10;
    
    if (argc < 2){
		fprintf (stderr, "Используйте %s <число>\n", argv[0]);
		exit (1);
	}
	
    sscanf(argv[1], "%d", &count);
    
    int size = sizeof(int)*count;
    
    /* Создадим область разделяемой памяти */
    if ((shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /* Получим доступ к разделяемой памяти */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /* Запишем в разделяемую память */
	s = shm;
	for (int i = 0; i < count; i++){
		s[i] = i; //*s++ = i;
	}
	
	pid_t pid;
	pid = fork();
	if (0 == pid) {

		/* Прочитаем из разделяемой памяти */
		s = shm;
		for (int i = 0; i < count; i++){
			printf("%d ", s[i]*s[i]);//s[i]*s[i] = *s**s++
		}	
		
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
