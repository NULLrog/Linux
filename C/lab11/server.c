/* Авиаразведка. Создается условная карта в виде матрицы, 
 * размерность которой определяет размер карты, 
 * содержащей произвольное количество единиц (целей) в произвольных ячейках. 
 * Из произвольной точки карты стартуют несколько разведчиков (процессов), 
 * курсы которых выбираются так, чтобы покрыть максимальную площадь карты. 
 * Каждый разведчик фиксирует цели, чьи координаты совпадают с его координатами 
 * и по достижении границ карты сообщает количество обнаруженных целей
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAPSIZE 5
int **map = NULL;

int myfunc(int num, int pi, int pj, int sock) {
    char buff[1024];
    int captured = 0;
    if(num == 0) {
        if(pi > MAPSIZE/2) {
			printf("Самолет с координатами %i %i вылетел налево\n", pi, pj);
			fflush(stdout);
            for(int i = pj; i > 0; i--) {
                if(map[pi][i] == 1){
                    captured++;
                }
            }
        } else {
			printf("Самолет с координатами %i %i вылетел направо\n", pi, pj);
			fflush(stdout);
            for(int i = pj; i < MAPSIZE; i++) {
                if(map[pi][i] == 1){
                    captured++;
                }
            }
        }
    } else {
        if(pj > MAPSIZE/2) {
			printf("Самолет с координатами %i %i вылетел вверх\n", pi, pj);
			fflush(stdout);
            for(int i = pi; i > 0; i--) {
                if(map[i][pj] == 1){
                    captured++;
                }
            }
        } else {
			printf("Самолет с координатами %i %i вылетел вниз\n", pi, pj);
			fflush(stdout);
            for(int i = pi; i < MAPSIZE; i++) {
                if(map[i][pj] == 1){
                    captured++;
                }
            }
        }
    }
    return captured;
}

void dostuff (int sock) {
    int n, status;
    int count;
    char buff[1024];
    char str1[] = "Введите количество самолетов";
    send(sock, &str1, strlen(str1), 0);
    if (((n = recv(sock, &buff[0], sizeof(buff) - 1, 0)) < 0)) {
        perror("Передача была оборвана!\n");
        exit(-1);
    }
    count = atoi(buff);
    pid_t pid[count];
    int pi = rand() % 5;
	int pj = rand() % 5;
    for(int i = 0; i < count; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            printf("При вызове fork() произошла ошибка!\n");
            exit(-2);
        } else if (pid[i] == 0) {
			int res = myfunc(i, pi, pj, sock);
            exit(res);
        }
    }
    for (int i = 0; i < count; i++) {
        if (pid[i] == waitpid(pid[i], &status, 0)) {
            printf("Самолет %d завершился, результат=%d\n", i, WEXITSTATUS(status));
            snprintf(buff, sizeof(buff), "Самолет %i захватил %i!", i, WEXITSTATUS(status));
			printf("%s\n", buff);
			send(sock, &buff, strlen(buff), 0);
			sleep(1);
        }
    }
    printf("КЛИЕНТ: ушел\n");
    return;
}

int **createMas(int count) {
    int **mas = malloc(count*sizeof(int *));
    printf("Карта:\n");
    for (int i = 0; i < count; i++) {
        mas[i] = malloc(count*sizeof(int));
        for (int j = 0; j < count; j++) {
            mas[i][j] = rand() % 2;
            printf("%d ",mas[i][j]);
        }
        printf("\n");
    }
    return mas;
}

int main(int argc, char *argv[]) {
    char buff[1024];
    printf("СЕРВЕР: начало работы\n");
    map = createMas(MAPSIZE);
    int sockfd, newsockfd;
    socklen_t clilen;
    int pid;
    struct sockaddr_in serv_addr, cli_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        perror("Сокет не был создал!\n");
        exit(-1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Сокет не был привязан!\n");
        exit(-1);
    }
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1) {
        if ((newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen)) < 0) {
            perror("Установка связи с клиентом оборвана!!\n");
            exit(-1);
        }
        printf("КЛИЕНТ: пришел\n");
        pid = fork();
        if (pid < 0)
            exit(-1);
        if (pid == 0) {
            dostuff(newsockfd);
            close(sockfd);
            exit(0);
        } else
            close(newsockfd);
    }
    close(sockfd);
    return 0;
}


