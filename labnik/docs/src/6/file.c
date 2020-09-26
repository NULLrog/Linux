#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// Программа из конспекта "Системное программное обеспечение"
// Версия для Linux
// стр. 44 
// Название: File
// Описание: обработка файла, подсчет кол-ва пробелов
// Входные параметры: fileName - имя файла для обработки
// Выходные параметры: кол-во пробелов в файле
int main(int argc, char *argv[]) {
    int handle, numRead, total= 0;
    char buf;
    if (argc<2) {
        printf("Usage: file textfile\n");
        exit(-1);
    }
    // запрос к ОС на открытие файла (только для чтения) 
    handle = open( argv[1], O_RDONLY);
    if (!handle) {
        printf("File not found %s!\n",argv[1]);
        exit(-2);
    }
    // цикл чтения до конца файла 
    do {
        // чтение одного символа из файла
        numRead = read( handle, &buf, 1);
        if (buf == 0x20) total++; } 
    while (numRead > 0);
    // закрытие файла
    close( handle); 
    printf("(PIO: %d), File %s, spaces = %d\n", getpid(), argv[1], total);
    return( total); 
}
