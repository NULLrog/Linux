#include <math.h>

double mypower(double input){
	return input*input;
}

double mysqrt(double input){
	if(input<0)
		return -1;
	else
		return sqrt(input);
}
