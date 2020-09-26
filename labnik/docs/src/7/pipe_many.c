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
    int fd[argc][2];
    for (i = 1; i < argc; i++) {
        pipe(fd[i]);
        pid[i] = fork();
        srand(getpid());
		
        if (-1 == pid[i]) {
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        } else if (0 == pid[i]) {
			/* процесс-потомок закрывает доступный для чтения конец канала 0*/
            close(fd[i][0]);
			/* записывает в канал 1*/
			int len = strlen(argv[i]);
			write(fd[i][1], &len, sizeof(int));
            exit(0);
        }
    }
    // если выполняется родительский процесс
    printf("PARENT: Это процесс-родитель!\n");
    // ожидание окончания выполнения всех запущенных процессов
    for (i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
			printf("процесс-потомок %d done,  result=%d\n", i, WEXITSTATUS(stat));
			/* процесс-родитель закрывает доступный для записи конец канала 1*/
			close(fd[i][1]);
			/* читает из канала 0*/
			int len = 0;
			read(fd[i][0], &len, sizeof(int));
			printf("i=%d len=%d\n", i, len );
        }
    }
    return 0;
}

