/*
 * В стандартной библиотеке языка С не определено никакой функции
 * записи целых значений типа short в файл
 * можно записывать в файл, пользуясь функцией fwrite(), 
 * но было бы нерационально применять этот способ для такой простой операции, 
 * как запись на диск целых значений типа short, 
 * так как получится чрезмерный перерасход ресурсов.
 *  
 */
 
#include <stdio.h>
#include <stdlib.h>

union pw {
  short int i;
  char ch[2];
};

int putw(short int num, FILE *fp);

int main(void)
{
  FILE *fp;
  fp = fopen("test.tmp", "wb+");
  if(fp == NULL) {
    printf("Файл не открыт.\n");
    exit(1);
  }
  putw(1025, fp);  /* запись значения 1025 */
  fclose(fp);
  return 0;
}

int putw(short int num, FILE *fp)
{
  union pw word;
  word.i = num;
  putc(word.ch[0], fp); /* записать первую половину */
  return putc(word.ch[1], fp); /* записать вторую половину */
}
