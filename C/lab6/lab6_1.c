/*
9. Контрольная сумма. Для нескольких файлов (разного размера) требуется
* вычислить контрольную сумму (сумму кодов всех символов файла).
* Обработка каждого файла выполняется в отдельном процессе.
*/
//--- fork_many.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int sum (char *file){
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
    int i, status; 
    pid_t pid[argc];
    if (argc < 3) {
        printf("Введите минимум 2 файла для подсчета контрольной суммы!\n");
        exit(-1);
    }
    for (i = 1; i < argc; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            printf("При вызове fork() произошла ошибка!\n");
            exit(-2);
        } 
        else if (pid[i] == 0) {
            printf("CHILD: Это %d процесс-потомок!\n", i);
            exit(sum(argv[i]));
        }
    }
    printf("PARENT: Это процесс-родитель!\n");
    for (i = 1; i < argc; i++) {
        if (pid[i] == waitpid(pid[i], &status, 0)) {
            printf("Потомок %d завершился, результат=%d\n", i, WEXITSTATUS(status));
        }
    }
    return 0;
}
