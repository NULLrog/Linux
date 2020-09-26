#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX_LEN 80

int main(int argc, char **argv){
	int fd[2];
	pid_t pid;
	char str[] = "Simple string\n";
	char buf[MAX_LEN];

	pipe(fd);
	pid = fork();
	if(-1 == pid){
		perror("fork");
		exit(1);
	} else if(0 == pid){
		/* процесс-потомок закрывает доступный для чтения конец канала 0*/
		close(fd[0]);
		/* записывает в канал 1*/
		write(fd[1], str, (strlen(str)+1));
		exit(0);
	} else {
		/* процесс-родитель закрывает доступный для записи конец канала 1*/
		close(fd[1]);
		/* читает из канала 0*/
		read(fd[0], buf, sizeof(buf));
		printf("Received string: %s", buf);
	}
	return(0);
}
