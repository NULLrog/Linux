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

int sum (char *file) {
    char ch;
    FILE *fp;
    if((fp = fopen(file, "r"))==NULL) {
        printf("Не удается открыть файл для чтения.\n");
        return -1;
    }
    int sum = 0;
    while((ch=fgetc(fp)) != EOF)
        sum+=ch;
    if(fclose(fp)) {
        printf("Ошибка при закрытии файла.\n");
        exit(-2);
    }
    return sum;
}

int main(void) {
    char buf[MAXLEN];
    int num, fd, ssum;
    pid_t pid;
    mkfifo(FIFO, 0666);
    printf("SERVER - Чтение входных данных\n");
    if (!(fd = open(FIFO, O_RDONLY))) {
        perror("Невозможно открыть FIFO");
        exit(-1);
    }

    while((num = read(fd, buf, sizeof(buf)))){
		buf[num] = '\0';
		ssum = sum(buf);
		printf("SERVER - контрольная сумма файла %s равна %d\n", buf, ssum);
		if(strstr(buf,"exit"))
			break;
	}
    close(fd);
    unlink(FIFO);
    return 0;
}
