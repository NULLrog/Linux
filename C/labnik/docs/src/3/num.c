#include <stdio.h>
struct numbers {
	int num1;
	int num2;
};
int main()
{
	//struct numbers s1 = {.num2 = 22, .num1 = 11};
	struct numbers s1 = { 22, 11 };
	// struct numbers s2 = {.num2 = 30};
	struct numbers s2 = { 2 };

	printf("num1: %d, num2: %d\n", s1.num1, s1.num2);
	printf("s2.num1: %d s2.num2: %d", s2.num1, s2.num2);
	return 0;
}
