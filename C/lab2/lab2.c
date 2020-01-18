/*
Вариант 9
Расположить строки по возрастанию длины первого слова 
Входные параметры:
1. Размерность массива 
2. Массив
Выходные параметры:
1. Максимальная длина слова 
2. Количество перестановок 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024 

int replace = 0;
int wordlen = 0; 

char** readMas(int count){
	printf("Введите строки для сортировки:\n");
	char buffer[MAX_LEN];
	char **mas = malloc(count*sizeof(char *));  
    for (int i = 0; i < count ; i++){
        scanf("%s", buffer); 
        mas[i] = malloc(strlen(buffer)*sizeof(char));
        strcpy(mas[i], buffer); 
    }
    return mas; 
}

int cmpstring(const void *p1, const void *p2){
	char **str1 = (char **)p1;
	char **str2 = (char **)p2;
	int compare = strcmp(*str1, *str2);
	if(compare > 0 || compare < 0)
		replace++;
	if (wordlen < strlen(*str1))
		wordlen = strlen(*str1);
	return compare;
}

void printMas(char **mas, int count){
	printf("Отсортированный массив:\n");
    for (int i = 0; i < count ; i++){
        printf("%s\n", mas[i]);
    }
}

void freeMas(char **mas, int count){
	for (int i = 0; i < count; i++){
        free(mas[i]);
    }
    free(mas);
}

int main(int argc, char **argv){
	char **mas = NULL;
	printf("Введите количество элементов в массиве: ");
	int count;
	scanf("%i", &count);
	mas = readMas(count);
	qsort(mas, count, sizeof(char *), cmpstring);
	printMas(mas, count);
	printf("Количество перестановок=%d\n", replace);
	printf("Максимальная длина слова=%d\n", wordlen);
	freeMas(mas, count);
}

