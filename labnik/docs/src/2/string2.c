#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMas(char *mas, int count){
    for (int i = 0; i < count ; i++){
        printf("%c", mas[i]);
    }
    printf("\n");
}

int main(int argc, char **argv){

	char message[] = "now is the time"; /* массив */
	char *p = "now is the time";  /* указатель на строковую константу*/
	message[0] = '?';
	printMas(message, strlen(message));
	//p[0] = "?"; //приведет к ошибке сегментирования (core dumped)
	printMas(p, strlen(p));
}

