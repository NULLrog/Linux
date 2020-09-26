#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	void catch(int);
	int waitstat;

	signal(SIGUSR1, catch);
	printf("Run this in another window: kill -s USR1 %d\n", getpid());
	for (;;) {
		printf("Going to sleep\n");
		sleep(3600);	/* for a good long time */
	}
}

void catch(int snum) {
	printf("got signal %d\n", snum);
	/* on SunOS systems, we have to  reset the signal catcher */
//	signal(SIGUSR1, catch);	/* don't need this on Linux or OS X (but doesn't hurt) */
}
