#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void doit(){
	pid_t pid;
	int status;
	pid = fork();
	
	if (-1 == pid) {
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else if (0 == pid){
		printf(" CHILD: Это процесс-потомок!\n");
		printf(" CHILD: Мой PID -- %d\n", getpid());
		printf(" CHILD: PID моего родителя -- %d\n", getppid());
		printf(" CHILD: Введите мой код возврата (как можно меньше):");
		scanf("%d", &status);
		printf(" CHILD: Выход!\n");
		exit(status); /* выход из процесс-потомока */ 
		/*
			ВНИМАНИЕ! НЕ ЗАБЫВАЙТЕ ДЕЛАТЬ return или exit.
		*/
	} else {
		printf("PARENT: Это процесс-родитель!\n");
		printf("PARENT: Мой PID -- %d\n", getpid());
		printf("PARENT: PID моего потомка %d\n",pid);
		printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
		if (wait(&status) == -1){
			perror("wait() error");
		} else if (WIFEXITED(status)){
			printf("PARENT: Код возврата потомка: %d\n", WEXITSTATUS(status));
		} else {
			perror("PARENT: потомок не завершился успешно");
		}
		printf("PARENT: Выход!\n");
	} //end if
}
	
int main(int argc, char** argv) {
	doit();
}
