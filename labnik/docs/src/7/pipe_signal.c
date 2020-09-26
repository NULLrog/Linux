/* 
 * gcc -g -Wall -o "pipe_signal2" "pipe_signal2.c" -std=gnu99 
 * 
 * */
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int main(int argc, char *argv[]) {
    int pid[argc], status, stat;       
    if (argc < 2) {
        printf("Usage: ./fork_many text text ...\n");
        exit(-1);
    }
    int fd[2];
	pipe(fd);
    sigset_t set; // List of expected signals
    sigemptyset(&set); // Init set
    sigaddset(&set, SIGUSR1); // Add signal USR1 to set
    sigprocmask(SIG_BLOCK, &set, NULL); 
    
    for (int i = 1; i < argc; i++) {
        pid[i] = fork();
        srand(getpid());
		
        if (-1 == pid[i]) {
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        } else if (0 == pid[i]) {
			
		//	close(fd[0]);
			int sig; 			
			pid_t pidd = getpid();
			/* записывает в канал 1*/
			write(fd[1], &pidd, sizeof(int));

			
			printf("процесс-потомок %d ожидает сигнала\n", pidd);
			fflush(stdout);
			
			sigwait(&set, &sig); // ждет сигнала от родительского процесса
	
			int len = strlen(argv[i]);
			write(fd[1], &len, sizeof(int));

			printf("процесс-потомок завершил\n");
			fflush(stdout);		
			
            return 0;
        }
    }
   // close(fd[1]);
	/* процесс-родитель закрывает доступный для записи конец канала 1*/
    sleep(1);
    // если выполняется родительский процесс
    printf("PARENT: Это процесс-родитель!\n");
    fflush(stdout);
    for (int i = 1; i < argc; i++) {
			pid_t ppid;
			read(fd[0], &ppid, sizeof(int));

			kill(ppid, SIGUSR1);
			printf("процессу-потомоку %d, отправлен сигнал\n", ppid);
			fflush(stdout);

    }
    // ожидание окончания выполнения всех запущенных процессов
    for (int i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
			printf("процесс-потомок %d done,  result=%d\n", pid[i], WEXITSTATUS(stat));

			int len = 0;
			read(fd[0], &len, sizeof(int));
			printf("процесс-потомок %d len=%d\n", pid[i], len );
			fflush(stdout);
        }
    }
    
    return 0;
}

