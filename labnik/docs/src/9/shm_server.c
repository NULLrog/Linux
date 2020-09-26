#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    
    /* Создадим область разделяемой памяти */
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
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
	/* Ожидаем окончания работы */
    while (*shm != -1)
        sleep(1);
	
	if (shmdt(shm) < 0) {
		printf("Ошибка отключения\n");
		exit(1);
	} 
	
	/* Удалим созданные объекты IPC */	
	 if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	}
    exit(0);
}
