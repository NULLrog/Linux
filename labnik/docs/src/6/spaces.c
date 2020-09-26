#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// Программа из конспекта "Системное программное обеспечение"
// Версия для Linux
// стр. 44, 77 
// Название: main 
// Описание: родительская программа 
// Входные параметры: список имен файлов для обработки 

// Выходные параметры: нет 
int main(int argc, char *argv[]) {
    int i, pid[argc], status, stat;
    char arg[20];
    // для всех файлов, перечисленных в командной строке 
    if (argc<2) {
        printf("Usage: file textfile1 textfile2 ...\n");
        exit(-1);
    }
    for (i = 1; i< argc; i++) { 
        // запускаем дочерний процесс 
        strcpy(arg,argv[i]);
        pid[i] = fork(); 
        if (pid[i] == 0) {
            // если выполняется дочерний процесс 
            // вызов функции счета количества пробелов в файле
            
            if (execl("./file","file",arg, NULL)<0) {
                printf("ERROR while start processing file %s\n",argv[i]);
                exit(-2);
            }
            else printf( "processing of file %s started (pid=%d)\n", argv[i],pid[i]);
        }
        // если выполняется родительский процесс
        
    }
    sleep(1);
    // ожидание окончания выполнения всех запущенных процессов
    for (i = 1; i< argc; i++) { 
        
        status=waitpid(pid[i],&stat,WNOHANG);
        if (pid[i] == status) {
            
            printf("File %s done,  result=%d\n",argv[i],WEXITSTATUS(stat));
        }
    }
    return 0; 
}
