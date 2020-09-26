#include <stdio.h>
#include <stdlib.h>
struct student{
    char name[50];
    int balls;
};
typedef struct student students;
 
void readStudent(students *st){
    printf("Введите Имя:");
    scanf("%s", st->name);
    printf("Введите баллы:");
    scanf("%d", &st->balls);
}

static int cmp(const void *p1, const void *p2){
    students * st1 = *(students**)p1;
    students * st2 = *(students**)p2;
    return st2->balls - st1->balls;
}
 
int main(int argc, char **argv){
    int count = 3;
    printf("Введите кол-во студентов:");
    scanf("%d", &count);
    students** st = (students**)malloc(sizeof(students*)*count);
    for (int i = 0; i < count ; i++){
        st[i] = (students*) malloc (sizeof(students));
        readStudent(st[i]);
    } 
    qsort(st, count, sizeof(students*), cmp);
    printf("Имя студента:%s\n", st[0]->name);
    printf("Балл:%d\n", st[0]->balls);
    for (int i = 0; i < count; i++)
    {
        free(st[i]);
    }
    free(st);
    return 0;
}
