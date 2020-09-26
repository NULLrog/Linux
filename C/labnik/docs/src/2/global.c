#include <stdio.h>
int x = 5; //Глобальная переменная
int add(int a, int b){
	int x = a + b; // локальная переменная
	printf("x-local=%d", x);
	return x;
}
int main( int argc, char *argv[] ) {
	int y = add(1, 2);
	printf("y=%d", y);
	printf("x-global=%d", x);
	return 0;
}
