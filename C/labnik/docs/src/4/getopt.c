#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]){
  int opt = 0;
  printf("%s ",argv[0]);
  int a, b, x, y = 0;
  while( (opt = getopt(argc, argv, ":a:b:x:")) != -1){
	switch (opt) {
		
    case 'a':
		a = atoi(optarg);
    break;

    break;

    case 'b':
		b = atoi(optarg);
    break;

    case 'x':
		x = atoi(optarg);
    break;
    
    default: /* '?' */
		fprintf(stderr, "Использование ax+b: %s [-a paramA] [-b paramB] [-x varible]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	  
    printf("-%c %s ", opt, optarg);
  };
  y = a*x + b;
  printf("\n");
  printf("a*x+b=%d", y);
  printf("\n");
  return 0;
}
