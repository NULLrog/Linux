#include <stdio.h>
struct point {
	int x;
	int y;
} a, b;

void display(struct point p)
{
	printf("x=%d\n", p.x);
	printf("y=%d\n", p.y);
}

int main(int argc, char **argv)
{
	a.x = 10;
	b = a;	/* присваение одной структуры другой */
	printf("%d \n", b.x);
	display(b);
	return 0;
}
