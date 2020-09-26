#include <stdio.h>
#define MAX_LEN 80
int main(int argc, char *argv[]){
	FILE *pipein_fp, *pipeout_fp;
	char readbuf[MAX_LEN];
	if (( pipein_fp = popen(argv[1], "r")) == NULL){
		perror("popen");
		exit(1);
	}
	while(fgets(readbuf, MAX_LEN, pipein_fp)){
		printf("%s",readbuf);
	}
	pclose(pipein_fp);
	return(0);
}
