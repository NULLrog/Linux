#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i, pid[argc], status, stat;
    if (argc < 2) {
        printf("Usage: ./fork_many text text ...\n");
        exit(-1);
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
            exit(strlen(argv[i])); /* выход из процесс-потомока */
        }
    }
    // если выполняется родительский процесс
    printf("PARENT: Это процесс-родитель!\n");
    // ожидание окончания выполнения всех запущенных процессов
    for (i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("процесс-потомок %d done,  result=%d\n", i, WEXITSTATUS(stat));
        }
    }
    return 0;
}

