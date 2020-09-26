#include <stdio.h>
#include <stdlib.h>

void write_string(char *str, FILE *fp){
  while(*str){ 
	if(!ferror(fp)){
		fputc(*str++, fp);
	}	
  }	
}

int main(int argc, char *argv[]){
	FILE *fp;
	if (argc < 3){
		fprintf (stderr, "Мало аргументов. Используйте <имя файла> <строка>\n");
		exit (1);
	}
	if((fp=fopen(argv[1], "a"))==NULL) {
		printf("Не удается открыть файл.\n");
		exit(1);
	}
	write_string(argv[2], fp);
	if(fclose(fp)){ 
		printf("Ошибка при закрытии файла.\n");
		exit(1);
	}
   return 0;
}
