#include <stdio.h>
#include <stdlib.h>
#define N 5
void test_malloc(int *p){
	p = (int *) malloc(N*sizeof(int));
	if(!p) {
		printf("Требуемая память не выделена[malloc].\n");
		exit(1);
	}

	for (int i = 0; i < N; i++){
		printf("p[%d]=%d ", i, p[i]); //доступ через p по индексу i
	}
	printf("\n");
	free(p);
}

void test_calloc(int *p){
	p = (int *) calloc(N, sizeof(int));
	if(!p) {
		printf("Требуемая память не выделена[calloc].\n");
		exit(1);
	}

	for (int i = 0; i < N; i++){
		printf("*(p+%d)=%d ", i, *(p+i)); //адресная арифметика
	}
	printf("\n");
	free(p);
}	

int main( int argc, char *argv[] ) {
	int *p = NULL;
	test_malloc(p);
	test_calloc(p);
}
