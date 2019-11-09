#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	char ch;
	FILE *fp;
	if((fp = fopen(argv[1], "r"))==NULL) {
        printf("Не удается открыть файл для чтения.\n");
        exit(-3);
    }
    int sum = 0;
    while((ch=fgetc(fp)) != EOF) 
		sum+=ch;
	printf("PID: %d Контрольная сумма файла %s = %d\n", getpid(), argv[1], sum);
	if(fclose(fp)) {
        printf("Ошибка при закрытии файла записи.\n");
        exit(-4);
    }
	return sum;
}
