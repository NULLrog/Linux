#include <stdio.h>
#include <string.h>

//неверно пишет длину массива
void len(char *name, int mas[]) {
	printf("%s funclen=%ld\n", name, sizeof(mas)/sizeof(int));
}	

int main(int argc, char **argv){
	int mas[3] = {0, 1, 3};
	int mas2[5] = {3, 4, 5, 6, 7};
	printf("mas len=%ld\n", sizeof(mas)/sizeof(int));
	len("mas", mas);
	printf("mas2 len=%ld\n", sizeof(mas2)/sizeof(int));
	len("mas2", mas2);
	return 0;
}

