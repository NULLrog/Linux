#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_return(){
	printf("Start\n");
	
	char array[30];
	gets(array);

	return strcmp(array, "password");
}

int main(int argc, char **argv){
	if (input_return()!=0){
		printf("No Pass\n");		
		exit(1);
	} 
	printf("Enter...\n");
	return 0;
}
