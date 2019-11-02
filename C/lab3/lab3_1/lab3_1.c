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

struct athlet {
    char surname[50];
    char sport[50];
    int countMedals;
};

int main(int argc, char **argv) {
    int count;
    printf("Введите кол-во спортсменов:");
    scanf("%d", &count);
    struct athlet athlets[count];
    for (int i = 0; i < count; i++) {
        printf("Введите Фамилию:");
        scanf("%s", athlets[i].surname);
        printf("Введите вид спорта:");
        scanf("%s", athlets[i].sport);
        printf("Введите количество медалей:");
        scanf("%d", &athlets[i].countMedals);
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("Фамилия спортсмена:%s\n", athlets[i].surname);
        printf("Вид спорта:%s\n", athlets[i].sport);
        printf("Количество медалей:%d\n", athlets[i].countMedals);
    }
}

