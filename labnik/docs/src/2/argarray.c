#include <stdio.h>

int sum( int a[], int len ){
	int s = 0;
	for(int i=0; i<len; i++) 
		s += a[i];
	return s;
}

double mean( int *a, int len ){
	double s = 0;
	for(int i=0; i<len; i++) 
		s += a[i];
	return s/len;
}

int main(int argc, char **argv){
	int a[] = {1, 2, 3};
	printf("Сумма массива:%d\n", sum(a, 3));
	printf("Среднее массива:%f\n", mean(a, 3));
}
