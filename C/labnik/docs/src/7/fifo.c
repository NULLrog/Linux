#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO1 "/tmp/fifo.1"
#define MAXLINE 80

void doit(char **argv){
	pid_t pid;
	int status = 0;
	int readfd, writefd;
	char buff[MAXLINE+1];
	ssize_t len, n;
	
	pid = fork();
	mkfifo(FIFO1, 0666);
	if (-1 == pid) {
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else if (0 == pid){
		printf(" CHILD: Это процесс-потомок!\n");
		len = strlen(argv[1]);
		writefd = open(FIFO1, O_WRONLY, 0);
		sleep(5);
		/* запись в канал IPC */
		write(writefd, argv[1], len);
		close(writefd);
		exit(status); /* выход из процесс-потомока */ 
	} else {
		printf("PARENT: Это процесс-родитель!\n");
		readfd = open(FIFO1, O_RDONLY, 0);
		len = strlen(argv[1]);
		/* считывание из канала */
		while ( (n = read(readfd, buff, len)) > 0);
		printf(buff);
		close(readfd); 
		if (wait(&status) == -1){
			perror("wait() error");
		} else if (WIFEXITED(status)){
			printf("PARENT: Код возврата потомка: %d\n", WEXITSTATUS(status));
		} else {
			perror("PARENT: потомок не завершился успешно");
		}
	} 
}

int main(int argc, char **argv){
	doit(argv);
	return 0;
}
