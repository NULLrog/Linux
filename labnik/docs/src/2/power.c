#include <stdio.h>
int power(int base, int n)
{
    int p;
    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}
int main( int argc, char *argv[] ) {
	int base = 2;
	int n = 3;
	printf("power=%d\n", power(base, n));
	printf("n=%d", n);
}
