#include <stdio.h>
#include <string.h>
#define MAX_LEN 80
void check(char *a, char *b, int (*cmp)(const char *, const char *)){
	printf("Проверка на совпадение.\n");
	if(!(*cmp)(a, b)) 
		printf("Равны");
	else 
		printf("Не равны");
}

int main(int argc, char **argv){
  char s1[MAX_LEN], s2[MAX_LEN];
  int (*p)(const char *, const char *); /* указатель на функцию */
  p = strcmp;   /* присваивает адрес функции strcmp указателю p */
  printf("Введите две строки.\n");
  fgets(s1, MAX_LEN, stdin);
  fgets(s2, MAX_LEN, stdin);
  check(s1, s2, p); /* Передает адрес функции strcmp
                       посредством указателя p */
  return 0;
}

