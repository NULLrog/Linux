/*
9
Оставить строки, содержащие заданное количество цифр
Параметры командной строки:
	1. Имя входного файла 
	2. Заданное количество цифр 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 128 

int main(int argc, char **argv) {
    FILE *fp;
    char str[128];
    int len;
    int count = 0;
    char **mas = NULL;  
    if (argc < 3) {
        fprintf (stderr, "Введите имя считываемого файла и количество цифр!\n");
        exit (-1);
    }
    int enterCount = atoi(argv[2]);
    if((fp = fopen(argv[1], "r"))==NULL) {
        printf("Не удается открыть файл для чтения.\n");
        exit(-1);
    }
    while(fgets(str, MAX_LEN, fp)) {
        int digitCount = 0;
        len = strlen(str);
        for (int i = 0; i < len; i++) {
            if(isdigit(str[i]))
                digitCount++;
        }
        if (digitCount == enterCount) {
			count++;
			mas = realloc(mas, count*sizeof(char *));
			if(!mas) {
				printf("Выделение памяти потерпело фиаско.\n");			
			}
			mas[count-1] = malloc(sizeof(char)*len);
			strcpy(mas[count-1],str);
		}
    }
    if(fclose(fp)) {
        printf("Ошибка при закрытии файла чтения.\n");
        exit(-1);
    }
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
    for (int i = 0; i < count; i++) {
		fputs(mas[i], fp);
		free(mas[i]);
	}
	free(mas);
	if(fclose(fp)) {
        printf("Ошибка при закрытии файла записи.\n");
        exit(-2);
    }
	printf("Поиск строк с заданным количеством цифр окончился успешно.\n");
    return 0;
}

