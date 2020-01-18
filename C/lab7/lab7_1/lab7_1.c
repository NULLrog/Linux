/*
9. Контрольная сумма. Для нескольких файлов (разного размера) требуется
* вычислить контрольную сумму (сумму кодов всех символов файла).
* Обработка каждого файла выполняется в отдельном процессе.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int sum (char *file) {
    char ch;
    FILE *fp;
    if((fp = fopen(file, "r"))==NULL) {
        printf("Не удается открыть файл для чтения.\n");
        exit(-3);
    }
    int sum = 0;
    while((ch=fgetc(fp)) != EOF)
        sum+=ch;
    printf("Контрольная сумма файла %s = %d\n", file, sum);
    if(fclose(fp)) {
        printf("Ошибка при закрытии файла записи.\n");
        exit(-4);
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int status, sums;
    int fd[argc][2];
    pid_t pid[argc];
    if (argc < 3) {
        printf("Введите минимум 2 файла для подсчета контрольной суммы!\n");
        exit(-1);
    }
    for (int i = 1; i < argc; i++) {
		pipe(fd[i]);
        pid[i] = fork();
        if (pid[i] == -1) {
            printf("При вызове fork() произошла ошибка!\n");
            exit(-2);
        } 
        else if (pid[i] == 0) {
            close(fd[i][0]);
            sums = sum(argv[i]);
            write(fd[i][1], &sums, sizeof(int));
            fflush(stdout);
            exit(sums);
        }
    }
    printf("PARENT: Это процесс-родитель!\n");
    for (int i = 1; i < argc; i++) {
        if (pid[i] == waitpid(pid[i], &status, 0)) {
            printf("Потомок %d завершился, результат=%d\n", i, WEXITSTATUS(status));
            close(fd[i][1]);
            read(fd[i][0], &sums, sizeof(int));
            printf("Потомок %d посчитал контрольную сумму=%d\n", i, sums);
            fflush(stdout);
        }
    }
    return 0;
}
