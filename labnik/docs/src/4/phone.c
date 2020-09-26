#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 20
#define NUM_LEN 20

struct phone{
	int group;
	char name[NAME_LEN];
	char num[NUM_LEN];
};

typedef struct phone phones;

FILE * open_file(char *name, char *mode) {
    FILE *fp;
    if ((fp = fopen(name, mode)) == NULL) {
        printf("Не удается открыть файл %s.\n", name);
        exit(1);
    }
    return fp;
}

void close_file(FILE *fp) {
    if (fclose(fp)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
}

void read_phones(FILE *fp) {
    phones ph;
    int size = sizeof (phones);
    while (!feof(fp)) {
        memset(ph.name, '\0', NAME_LEN);
        memset(ph.num, '\0', NUM_LEN);
        if (fread(&ph, size, 1, fp) == 1) {
            printf("Group:%d ", ph.group);
            printf("Name:%s ", ph.name);
            printf("Num:%s\n", ph.num);
        }
    }
}

void write_phone(FILE *fp, char *argv[]) {
    phones ph;
    ph.group = atoi(argv[2]);
    memset(ph.name,'\0', NAME_LEN);
    memset(ph.num,'\0', NUM_LEN);
    strcpy(ph.name, argv[3]);
    strcpy(ph.num, argv[4]);
    fwrite(&ph, sizeof(phones), 1, fp);
}

int main(int argc, char **argv)
{
    FILE *fp;
    if (argc < 2) {
        fprintf(stderr,	"Мало аргументов. Используйте для чтения <имя файла>\n");
        fprintf (stderr, "Используйте для записи <имя файла> <group> <name> <num>\n");
        exit(1);
    } else if(argc ==2){
		fp = open_file(argv[1], "rb");
		read_phones(fp);
		close_file(fp);
	} else if (argc < 5 ) {
        fprintf (stderr, "Мало аргументов. Используйте <имя файла> <group> <name> <num>\n");
        exit (1);
    } else if(argc == 5){
		fp = open_file(argv[1], "ab");
		write_phone(fp, argv);
		close_file(fp);
	} if (argc > 5){
		fprintf (stderr, "Много аргументов. Используйте <имя файла> <group> <name> <num>\n");
        exit (1);
	}
    return 0;
}
