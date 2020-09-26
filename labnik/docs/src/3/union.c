#include <stdio.h>

union u_type {
  int i;
  char ch;
};

struct point{
  int i;
  char ch;
}; 

int main(int argc, char **argv){
  struct point s = {1, 'A'};
  union u_type u = {'A'};
  
  printf("size of union = %i\n", sizeof(u));
  printf("size of structure = %i\n", sizeof(s));

  printf("union.ch = %c\n", u.ch);
  printf("ASCII code union.i = %i\n", u.i);
  u.i++; 
  printf("union.ch = %c\n", u.ch);
  printf("ASCII code union.i = %i\n", u.i);

  printf("struct.ch = %c\n", s.ch);
  printf("ASCII code struct.i = %i\n", s.i);
  s.i++; 
  printf("struct.ch = %c\n", s.ch);
  printf("ASCII code struct.i = %i\n", s.i);

  return 0;
}
