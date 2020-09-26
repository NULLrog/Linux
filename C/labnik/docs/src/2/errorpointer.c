#include <stdio.h>

int main(int argc, char **argv){

	int *iptr;
    // printf("%d\n", *iptr); //Ошибка сегментирования (core dumped)
    // *iptr = 10; //Ошибка сегментирования (core dumped)
	
	int i = 2;
	double x = 12.06;
	
	iptr= &i;	
	printf("%d\n", *iptr);
	printf("%d\n", *(iptr+1));
	iptr += 7;  /* куда же он указал ?! */

	iptr = (int *)&x; 
	i = *iptr;
	printf("%d\n", i);
	
	double y = *((double *)iptr); 
	printf("%f\n", y);

}
