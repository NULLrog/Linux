#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
  FILE *fp;
  float f = 77.7;
   
  if (argc < 2){
		fprintf (stderr, "Мало аргументов. Используйте <имя файла>\n");
		exit (1);
  }
  
  if((fp=fopen(argv[1], "wb"))==NULL) {
    printf("Не удается открыть файл.\n");
    exit(1);
  }
  fwrite(&f, sizeof(float), 1, fp);

  if(fclose(fp)){ 
	printf("Ошибка при закрытии файла.\n");
	exit(1);
  }

  printf("f=%f\n", f);
  return 0;
} 
