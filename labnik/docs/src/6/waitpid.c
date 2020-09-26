#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t pid, w;
    int status;
    pid = fork();
    if (-1 == pid) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (0 == pid) { /* Код, выполняемый потомком */
        printf("Child PID is %ld\n", (long) getpid());
        if (1 == argc)
            pause(); /* Ожидание сигналов */
        _exit(atoi(argv[1])); /* выход из процесс-потомока */ 
    } else { /* Код, выполняемый родителем */
        do {
            w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            if (-1 == w) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        exit(EXIT_SUCCESS);
    }
}

