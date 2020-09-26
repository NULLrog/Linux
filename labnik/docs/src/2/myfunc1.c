#include <stdio.h>
int myfunc(int a, int b, float c){
//тело функции
	printf("a=%d b=%d c=%f", a, b, c);
	return 0;
}

int main( int argc, char *argv[] ) {
	myfunc(1,2,3);//вызов функции 1,2,3 — аргументы функции.
	return 0;
}
