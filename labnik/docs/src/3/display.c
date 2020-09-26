#include <stdio.h>
struct point {
	int x;
	int y;
};

void display(struct point p)
{
	printf("x=%d\n", p.x);
	printf("y=%d\n", p.y);
}

void move(struct point *p, int dx, int dy)
{
	p->x += dx;
	p->y += dy;
}

int main(int argc, char **argv)
{
	struct point p = { 200, 300 };
	struct point *pp = &p;
	move(&p, 20, 30);
	display(*pp);
	return 0;
}
