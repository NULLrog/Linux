#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phone.h"

int main(int argc, char ** argv) {
    FILE *fp;

    if (argc < 2) {
        fprintf (stderr, "Мало аргументов. Используйте <имя файла>\n");
        exit (1);
    }

    if((fp=fopen(argv[1], "rb"))==NULL) {
        printf("Не удается открыть файл.\n");
        exit(1);
    }
    phones ph;
    int size = sizeof(phones);
    while(!feof(fp)) {
        memset(ph.name,'\0', NAME_LEN);
        memset(ph.num,'\0', NUM_LEN);
        if (fread(&ph, size, 1, fp) == 1) {
            printf("Group:%d\n", ph.group);
            printf("Name:%s\n", ph.name);
            printf("Num:%s\n", ph.num);
        }
    }

    if(fclose(fp)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
    return 0;
}
