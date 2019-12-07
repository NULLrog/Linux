/*5.Винни-Пух и пчелы. Заданное количество пчел добывают мед равными порциями,
* задерживаясь в пути на случайное время.
* Винни-Пух потребляет мед порциями заданной величины за заданное время и
* столько же времени может прожить без питания.
* Работа каждой пчелы реализуется в порожденном процессе.*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define HONEY 500
#define BEAR 300
#define BEE 5

int *shm;
int semid, shmid;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;

    struct seminfo *__buf;
};

struct sembuf lock_res = {0, -1, 0};
struct sembuf rel_res = {0, 1, 0};

void sighandler(int signum) {
	printf("Сигнал о смерти медведя получен!\n");
	exit(0);
}

void attach() {
    if ((shm = (int *)shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("Не удалось получить доступ к разделяемой памяти!\n");
        exit(-4);
    }
}

void detach() {
    if (shmdt(shm) < 0) {
        printf("Ошибка отключения\n");
        exit(-5);
    }
}

void semlock(int i) {
    if((semop(semid, &lock_res, 1)) == -1) {
        perror("Ошибка блокировки улия!");
        exit(1);
    } else {
        printf("Улий заблокирован потомком %d\n", i+1);
        fflush(stdout);
    }
}
void semrel(int i) {
    if((semop(semid, &rel_res, 1)) == -1) {
        perror("Ошибка разблокировки улия!\n");
        exit(1);
    } else {
        printf("Улий разблокирован потомком %d\n", i+1);
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) {
    pid_t pid[atoi(argv[1])+1];
    int status, stat;
	int bearDeath = 0;
    key_t key;
    union semun arg;

    if (argc < 2) {
        printf("Введите количество пчел!\n");
        exit(-1);
    }

    key = ftok("Makefile", 'k');
    if((semid = semget(key, 1, IPC_CREAT | 0660)) < 0) {
        perror("Не удалось создать семафор!\n");
        exit(-2);
    }
    if ((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("Не удалось создать область разделяемой памяти!\n");
        exit(-3);
    }
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    attach();
    *shm = HONEY;
    detach();
    printf("Бочка: Создано %d единиц меда!\n", HONEY);
    fflush(stdout);

    for (int i = 0; i < atoi(argv[1])+1; i++) {
        pid[i] = fork();
		
        if (pid[i] == -1) {
            perror("Ошибка создания пчелы или медведя!\n");
            exit(-6);
        }

        else if (pid[i] == 0) {
			signal(SIGTERM, sighandler);
            while(bearDeath!=1) {
                attach();
                semlock(i);
                if(i == atoi(argv[1])) {
                    if (*shm < BEAR) {
                        printf("МЕДВЕДЬ: Приказал жить долго, мёда осталось %d!\n", *shm);
                        bearDeath = 1;
                        for (int j = 0; j < atoi(argv[1]); j++)
							kill(pid[i], SIGTERM);	
                        semrel(i);
                        detach();
                        exit(1);
                    } else {
                        *shm -= BEAR;
                        sleep(rand() % 4);
                        printf("МЕДВЕДЬ: Съел %d мёда, осталось %d!\n", BEAR, *shm);
                        fflush(stdout);
                    }
                } else {
                    *shm += BEE;
                    sleep(rand() % 2);
                    printf("ПЧЕЛА: Принесла %d мёда, стало %d!\n", BEE, *shm);
                    fflush(stdout);
                }
                semrel(i);
                detach();
            }
            exit(0);
        }
    }
    for (int i = 0; i < atoi(argv[1])+1; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("Потомок %d завершился, result=%d\n", i+1, WEXITSTATUS(stat));
            fflush(stdout);
        }
    }
    
    if (shmctl(shmid, IPC_RMID, 0) < 0) {
        printf("Невозможно удалить разделяемую память\n");
        exit(-1);
    } else
        printf("Разделяемая память была удалена\n");

    if (semctl(semid, 0, IPC_RMID) < 0) {
        printf("Невозможно удалить семафор\n");
        exit(-1);
    }
    return 0;
}
