/*
3.Операции возведения в квадрат и извлечения корня.
*/

#include <stdio.h>

double mypower(double input);
double mysqrt(double input);

int main(int argc, char **argv) {
	double x = 4;
    double y = mypower(x);
    printf("Квадрат числа %f = %f\n", x, y);
    y = mysqrt(x);
	printf("Корень числа %f = %f\n", x, y);
    return 0;
}

