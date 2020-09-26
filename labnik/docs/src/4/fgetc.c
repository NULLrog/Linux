#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  FILE *fp;
  char ch;

  if((fp=fopen(argv[1],"r"))==NULL) {
    printf("Невозможно открыть файл.\n");
    exit(1);
  }

  while((ch=fgetc(fp)) != EOF) {
    printf("%c", ch);
  }
  
  fclose(fp);
  return 0;
}
