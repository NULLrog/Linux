#include <stdio.h>
#include <string.h>

struct student {
	int id;
	char name[20];
	float percent;
};

int main()
{
	struct student rec = { 10, {'I', 'v', 'a', 'n'}, 10.5 };
	rec.id = 1;
	strcpy(rec.name, "Petr");
	//rec.name = "error";
	rec.percent = 86.5;

	printf(" Id: %d \n", rec.id);
	printf(" Name: %s \n", rec.name);
	printf(" Percent: %f \n", rec.percent);
	return 0;
}
