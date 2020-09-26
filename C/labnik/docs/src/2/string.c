#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char s1[80], s2[80];
	scanf("%s", s1);
	scanf("%s", s2);
	printf("Длина: %ld %ld\n", strlen(s1), strlen(s2));
	if(!strcmp(s1, s2)) 
		printf("Строки равны\n");
	strcat(s1, s2);
	printf("%s\n", s1);
	strcpy(s1, "Проверка.\n");
	printf("%s", s1);
	if(strchr("Алло", 'л')) printf(" л есть в Алло\n");
	if(strstr("Привет", "ив")) printf(" найдено ив ");
  return 0;
}

