#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phone.h"

int main(int argc, char ** argv) {
    FILE *fp;

    if (argc < 4) {
        fprintf (stderr, "Мало аргументов. Используйте <имя файла> <group> <name> <num>\n");
        exit (1);
    }

    if((fp=fopen(argv[1], "ab"))==NULL) {
        printf("Не удается открыть файл.\n");
        exit(1);
    }
    phones ph;
    ph.group = atoi(argv[2]);
    memset(ph.name,'\0', NAME_LEN);
    memset(ph.num,'\0', NUM_LEN);
    strcpy(ph.name, argv[3]);
    strcpy(ph.num, argv[4]);

    fwrite(&ph, sizeof(phones), 1, fp);

    if(fclose(fp)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
    return 0;
}
