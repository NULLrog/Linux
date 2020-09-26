#include <mcheck.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int j;
	mtrace(); /* подключаем логи вначале программы */
	for (j = 0; j < 2; j++)
		malloc(100);            /* никогда не освободиться - утечка */
        calloc(16, 16);             /* никогда не освободиться - утечка */
        exit(EXIT_SUCCESS);
}
