#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    FILE *fp;

    if (argc < 3) {
        fprintf (stderr, "Мало аргументов. Используйте <имя файла> <num1> <num2> ...\n");
        exit (1);
    }

    if((fp=fopen(argv[1], "wb"))==NULL) {
        printf("Не удается открыть файл.\n");
        exit(1);
    }
    int n = argc - 2;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = atoi(argv[i + 2]);
    }

    fwrite(a, sizeof(int), n, fp);

    if(fclose(fp)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
    return 0;
}
