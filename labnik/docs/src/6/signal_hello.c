#include <stdio.h>      /* Input/Output */
#include <signal.h>     /* Signal handling */

void hello(int signum){
  printf("Hello World!\n");
}

int main(){

  //Handle SIGINT with hello
  signal(SIGINT, hello);

  //loop forever!
  while(1);

}
