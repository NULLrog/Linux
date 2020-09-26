#include <signal.h>
                         #include <stdio.h>
                         struct two_words { int a, b; } memory;
                         void
                         handler(int signum)
                         {
                                 printf ("%d,%d\n", memory.a, memory.b);
                                 alarm (1);
                         }
                         int
                         main (void)
                         {
                                 static struct two_words zeros = {0,0},
                                                          ones  = {1,1};
                                 signal (SIGALRM, handler);
                                 memory = zeros;
                                 alarm (1);
                                 while (1)
                                 {
                                         memory = zeros;
                                         memory = ones;
                                 }
                         }
