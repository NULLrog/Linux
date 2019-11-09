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
			if (execl("./file", "file", argv[i], NULL)<0) {
				printf("Ошиька открытия файла %s\n",argv[i]);
				exit(-5);
			}
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
