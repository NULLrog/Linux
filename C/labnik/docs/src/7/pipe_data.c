#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX_LEN 80

int main(int argc, char **argv){
	int fd[2];
	pid_t pid;
	char str[] = "Simple string";
	char str2[] = "test";
	char buf[MAX_LEN];
	char buf2[MAX_LEN];
	memset(buf, '\0', MAX_LEN);
	memset(buf2, '\0', MAX_LEN);
	pipe(fd);
	pid = fork();
	if(-1 == pid){
		perror("fork");
		exit(1);
	} else if(0 == pid){
		/* процесс-потомок закрывает доступный для чтения конец канала 0*/
		//close(fd[0]);
		/* записывает в канал 1*/
		int len = strlen(str);
		write(fd[1], &len, sizeof(int));
		write(fd[1], str, len);

		int len2 = strlen(str2);
		write(fd[1], &len2, sizeof(int));
		write(fd[1], str2, len2); 
		sleep(5);
		
		len = 0;
		printf("Child process exit!");
		read(fd[0], &len, sizeof(int));
		printf("Child len=%d", len);
		fflush(stdout);
		exit(0);
	} else {
		
		/* процесс-родитель закрывает доступный для записи конец канала 1*/
		//close(fd[1]);
		/* читает из канала 0*/
		int len = 0;// = strlen(str);
		read(fd[0], &len, sizeof(int));
		if (len >0)
			read(fd[0], buf, len);
		printf("Received len=%d string: %s\n", len, buf);
		
		int len2 = 0;
		read(fd[0], &len2, sizeof(int));
		if (len2 >0)
			read(fd[0], buf2, len2);
		printf("Received len=%d string: %s\n", len2, buf2);
		fflush(stdout);
		write(fd[1], &len, sizeof(int));
	}
	return(0);
}
