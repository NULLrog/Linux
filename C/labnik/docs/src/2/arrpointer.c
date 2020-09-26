#include <stdio.h>
#define N 10

int main( int argc, char *argv[] ) {
	int a[N]; //объявление массива
	for (int i = 0; i < N; i++){
		printf("a[%d]=%d ", i, a[i]); //доступ по индексу i
	}
	printf("\n");
	int *p = &a[0];
	for (int i = 0; i < N; i++){
		printf("p[%d]=%d ", i, p[i]); //доступ через p по индексу i
	}
	printf("\n");
	p = a;
	for (int i = 0; i < N; i++){
		printf("*(p+%d)=%d ", i, *(p+i)); //адресная арифметика
	}
	printf("\n");
}
