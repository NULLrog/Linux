#include <stdio.h>
#define N 8
struct simple {
   char a; /* 4 байта */
   int  i; /* 4 байта */
};
 
struct packed {
   char a; /* 1 байт */
   int i; /* 4 байта */
}__attribute__((packed));
 
int main( int argc, char* argv[] ) {
 
  struct simple s1;
  struct packed s2;
 
  printf( "sizeof s1 is %d\n" , sizeof(s1) );
  printf( "sizeof s2 is %d\n" , sizeof(s2) );
 
  struct simple *p1;
  struct packed *p2;
  char mass[N];
  mass[0]='a';
  mass[1]='c';
  for (int i = 2; i < N ; i++){
        mass[i]='b';
   }
  p1 = mass;
  printf("%c\n",p1->a);//под char выделено 4 байта
  printf("%c\n",p1->i);//c 5-го байта
 
  p2 = mass;
  printf("%c\n",p2->a);
  printf("%c\n",p2->i);//c 2-го байта
 
  return( 0 );
}
