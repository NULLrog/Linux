#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
		
        pid_t pid = fork();	/* fork returns type pid_t */
        srand(getpid());
        int t = rand()%4;
        printf("sleep time=%d pid=%d \n", t, pid);
        sleep(t);
        printf("fork() returned %d\n",  pid);
}
