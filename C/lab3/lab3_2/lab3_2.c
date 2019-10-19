/*
Вариант 9
Фамилия спортсмена 
Вид спорта 
Количество медалей
Расположить в алфавитном порядке записи с ненулевым количеством медалей 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct athlet{
	char surname[50];
	char sport[50];
	int countMedals;
};

void readAthlet(struct athlet *a){
	printf("Введите Фамилию:");
    scanf("%s", a->surname);
    printf("Введите вид спорта:");
    scanf("%s", a->sport);
    printf("Введите количество медалей:");
    scanf("%d", &a->countMedals);
    
}

void printAthlet(struct athlet *a){
	printf("Фамилия спортсмена:%s\n", a->surname);
	printf("Вид спорта:%s\n", a->sport);
	printf("Количество медалей:%d\n", a->countMedals);
}

static int cmp(const void *p1, const void *p2){
		struct athlet *a1 = *(struct athlet**)p1;
		struct athlet *a2 = *(struct athlet**)p2;
		if (a2->countMedals > 0)
			return strcmp(a1->surname, a2->surname);
		else
			return 0;
}

int main(int argc, char **argv){
	int count;
    printf("Введите кол-во спортсменов:");
    scanf("%d", &count);
	struct athlet **athlets = malloc(sizeof(struct athlet*)*count);
	for (int i = 0; i < count; i++) {
		athlets[i] = malloc (sizeof(struct athlet));
        readAthlet(athlets[i]);
	}
	printf("\n");
	for (int i = 0; i < count; i++) {
		printAthlet(athlets[i]);
	}
	printf("\n");
	qsort(athlets, count, sizeof(struct athlet*), cmp);
	printf("Спортсмены после сортировки:\n");
	for (int i = 0; i < count; i++) {
		printAthlet(athlets[i]);
	}
	for (int i = 0; i < count; i++) {
		free(athlets[i]);
	}
	free(athlets);
}

