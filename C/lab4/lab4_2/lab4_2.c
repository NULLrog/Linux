/*
9
После каждого пробела вставить точку 
Параметры командной строки:
	1. Имя входного файла 
	2. Количество вставок 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *fp;
    char *mas = NULL;
    char ch; 
    if (argc < 3) {
        fprintf (stderr, "Введите имя считываемого файла и количество вставок!\n");
        exit (-1);
    }
    int enterCount = atoi(argv[2]);
    if((fp = fopen(argv[1], "r"))==NULL) {
        printf("Не удается открыть файл для чтения.\n");
        exit(-1);
    }
    int count = 0;
    while((ch=fgetc(fp)) != EOF) {
		count++;
		mas = realloc(mas, sizeof(char)*count);
		mas[count-1] = ch;
		if(ch == ' ') {
			mas = realloc(mas, sizeof(char)*(count+enterCount));
			for (int j = 0; j < enterCount; j++)
				mas[count+j] = '.';
			count+=enterCount;
		}
	}
    if(fclose(fp)) {
        printf("Ошибка при закрытии файла чтения.\n");
        exit(-1);
    }
    char str[128];
    strcpy(str,argv[1]);
    char temp[10]= "\0";
    for (int i = 0; i < strlen(str); i++) {
		if(str[i]=='.') {
			strncpy(temp, str, i+1);
			break;
		}
	}
	strcat(temp,"out");
	if((fp = fopen(temp, "w"))==NULL) {
        printf("Не удается открыть файл для записи.\n");
        exit(-2);
    }
    for (int i = 0; i < count; i++) 
		fputc(mas[i], fp);
	free(mas);
	if(fclose(fp)) {
        printf("Ошибка при закрытии файла записи.\n");
        exit(-2);
    }
	printf("Поиск строк с звставка окончился успешно.\n");
    return 0;
}

