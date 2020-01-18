/*
9. Контрольная сумма. Для нескольких файлов (разного размера) требуется
* вычислить контрольную сумму (сумму кодов всех символов файла).
* Обработка каждого файла выполняется в отдельном процессе.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define FIFO "/tmp/fifo.txt"
#define MAXLEN 64

int main(void) {
    char buf[MAXLEN];
    int num, fd;
    if (!(fd = open(FIFO, O_WRONLY))) {
        perror("Невозможно открыть FIFO");
        exit(-1);
    }
    printf("CLIENT - Запись входных параметров\n");
    while (1) {
        scanf("%s",buf);
        if(strstr(buf,"exit"))
            break;
        num = write(fd, buf, strlen(buf));
		printf("CLIENT записал в %s - %d байт\n", FIFO, num);
    }
    close(fd);
    return 0;
}
