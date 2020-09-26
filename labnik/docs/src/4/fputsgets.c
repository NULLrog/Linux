#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
int main (int argc, char **argv)
{
    if (argc < 2) {
        printf("Неверное кол-во параметров\n");
        exit(1);
    }

    FILE *fp, *fp2;
    if ((fp = fopen (argv[1], "r")) == NULL)
    {
        printf ("Невозможно открыть файл.\n");
        exit (1);
    }

    if ((fp2 = fopen (argv[2], "w")) == NULL)
    {
        printf ("Невозможно открыть файл.\n");
        exit (1);
    }

    char buffer[N];
    int maxlen = atoi (argv[3]);

    while(!feof(fp)) {
        memset(buffer, '\0',N);
        if(fgets(buffer, N, fp))
        {
            if (strlen(buffer) < maxlen)
            {
                fputs(buffer, fp2);
                printf("%s", buffer);
            }
        }
    }
    fclose (fp2);
    fclose (fp);
    return 0;
}
