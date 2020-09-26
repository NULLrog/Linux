#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    key_t key = 5678;
    int *shm, *s, shmid, count = 10;

    if (argc < 3){
		fprintf (stderr, "Используйте %s <ключ> <кол-во чисел>\n", argv[0]);
		exit (1);
	}

    sscanf(argv[1], "%d", &key);
    sscanf(argv[2], "%d", &count);
    int size = sizeof(int)*count;
    
     /* Подключим область разделяемой памяти */
    if ((shmid = shmget(key,  size, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /* Получим доступ к разделяемой памяти */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
	/* Делаем копию */
    s = shm;
    
	/* Прочитаем из разделяемой памяти */
    for (int i = 0; i < count; i++){
		printf("%d", *s);
		s++;
	}

	/* Запишем окончание работы */
    *shm = -1;
    
    if (shmdt(shm) < 0) {
		printf("Ошибка отключения\n");
		exit(1);
	} 
    exit(0);
}
