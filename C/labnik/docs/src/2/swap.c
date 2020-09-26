#include <stdio.h>
void swap(int *x, int *y){
  int temp;
  temp = *x;  /* сохранить значение по адресу x */
  *x = *y;    /* поместить y в x */
  *y = temp;  /* поместить x в y */
}
int main(int argc, char *argv[]){
  int i = 10, j = 20;
  printf("i и j перед обменом значениями: %d %d\n", i, j);
  swap(&i, &j); /* передать адреса переменных i и j */
  printf("i и j после обмена значениями: %d %d\n", i, j);
  return 0;
}
