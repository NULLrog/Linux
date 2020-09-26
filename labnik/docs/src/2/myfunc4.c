#include <stdio.h>
int x; //Глобальная переменная
int add(int a, int b){ //функция возвращает int
	//тело функции
	return a+b; //возврат результата 
}
void addvoid(int a, int b){
	x = a+b;
}

int main( int argc, char *argv[] ) {
	x = add(1,2);
	x = add(1, add(2,3));
	addvoid(x, x);
	printf("x=%d", x);
	return 0;
}

