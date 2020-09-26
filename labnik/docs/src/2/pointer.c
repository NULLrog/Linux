#include <stdio.h>
int main( int argc, char *argv[] ) {
	int x = 10;
	int *p;
	p = &x;
	*p = 11;
	printf("x=%d\n", x);
	printf("*p=%d\n", *p);
	printf("p=%p\n", p);
	printf("&x=%p\n", &x);
	printf("&p=%p\n", &p);
}
