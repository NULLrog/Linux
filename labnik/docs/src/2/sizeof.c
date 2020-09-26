#include <stdio.h>
#include <string.h>
#define LEN 10
void print(char *text, char *mas){
	printf("%s = %s, sizeof=%ld, strlen=%ld\n", text, mas, sizeof(mas), strlen(mas));
}	

void showMas2(char *mas){
		mas[2] = 'C';
		mas[3] = 'D';
		print("showMas2", mas);
}

void showMas(char mas[]){
		mas[0] = 'A';
		mas[1] = 'B';
		print("showMas", mas);
		showMas2(mas);
		print("showMas", mas);
}

int main(int argc, char **argv){
	char mas[LEN];
	memset(mas, '\0', LEN);
	//print("mas", mas);
	printf("mas = %s, sizeof=%ld, strlen=%ld\n", mas, sizeof(mas), strlen(mas));
	showMas(mas);
	return 0;
}

