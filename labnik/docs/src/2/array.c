#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h> /* для mtrace */
#include <string.h>
#define MAX_LEN 1024 /* максимальная длина строки */

char** readMas(int count){
	char buffer[MAX_LEN];
	char **mas;  //указатель на массив указателей на строки
	mas = (char **)malloc(sizeof(char *)*count);// выделяем память для массива указателей
    for (int i = 0; i < count ; i++){
        scanf("%s", buffer); // читаем строку в буфер
        mas[i] = (char *)malloc(sizeof(char)*strlen(buffer)); //выделяем память для строки
        strcpy(mas[i], buffer); //копируем строку из буфера в массив указателей
    }
    return mas; 
}

void printMas(char **mas, int count){
    for (int i = 0; i < count ; i++){
        printf("%s\n", mas[i]);
    }
}

void freeMas(char **mas, int count){
	for (int i = 0; i < count; i++){
        free(mas[i]); // освобождаем память для отдельной строки
    }
    free(mas); // освобождаем памать для массива указателей на строки
}

int main(int argc, char **argv){

	char **mas = NULL; //указатель на массив указателей на строки
	int count = 3;
	mtrace();
	mas = readMas(count);
	printMas(mas, count);
	freeMas(mas, count);
}
