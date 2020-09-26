#include <stdio.h>
#define N 10

int main( int argc, char *argv[] ) {
	int a[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int *p = a;
	for (int i = 0; i < N; i++){
		printf("*(p+%d)=%d", i, *(p+i)); //адресная арифметика
	}
	printf("\n");
	p = a;
	for (int i = 0; i < N; i++){
		printf("p[%d]=%d", i, p[i]); //доступ через p по индексу i
	}

	printf("\n");
} 
