#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *end;
	if (argc < 2){
        printf("Неверное кол-во параметров\n");
        exit(1);
    }    
  	printf("argv[0]=%s\n", argv[0]);
	printf("argv[1]=%ld\n", strtol(argv[1], &end, 10));
	printf("argv[1]=%d\n", atoi(argv[1]));
	return 0;
} 
