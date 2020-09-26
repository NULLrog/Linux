#include <stdio.h>
int main(int argc, char **argv){
  int x = 10, *p, **q;
  p = &x;
  q = &p;
  printf("%d", **q); /* печать значения x */
  return 0;
}
