#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12345
#define ADR "127.0.0.1"
#define MSG_MAX 10
#define BUFSIZE 256

void msg_gen(char *s, int len) {
    char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        s[i] = alpha[(rand()+getpid()) % (sizeof(alpha) - 1)];
    }
    s[len] = '\0';
}


int main(int argc, char *argv[]) {
    sleep(1);
    int sockfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in server;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(ADR);

    while(1) {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
            perror("Ошибка открытия сокета");
            exit(-1);
        }
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Ошибка соединения");
            exit(-1);
        } else {
            char buf[BUFSIZE];
            read(sockfd, buf, sizeof(buf));
            buf[strlen(buf)] = '\0';
            struct sockaddr_in multicast_addr;
            int mcPort = atoi(buf);
            int bufLen;
            int sockmc;
            if ((sockmc =socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket()");
                exit(-1);
            }
            multicast_addr.sin_family = AF_INET;
            multicast_addr.sin_addr.s_addr = INADDR_ANY;
            multicast_addr.sin_port = htons(mcPort);
            if (bind (sockmc, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0) {
                perror("bind()");
                exit(-1);
            }
            while(1) {
                memset(buf,0,sizeof(buf));
                bufLen = recvfrom(sockmc, buf, BUFSIZE, 0, NULL, 0);
                if (bufLen == 0)
                    break;
                buf[bufLen] = '\0';
                if (strcmp(buf, "Пиши") == 0) {
                    printf("%s\n", buf);
                    write(sockfd, "1", 1);
                    char randoms[MSG_MAX];
                    msg_gen(randoms, MSG_MAX);
                    memset(buf,0,sizeof(buf));
                    sprintf(buf, "%s", randoms);
                    strcat(buf, "\0");
                    send(sockfd, buf, MSG_MAX, 0);
                    printf("Отправлено: %s\n", buf);
                    sleep(1 + rand() % 8);
                    break;
                } else {
                    printf("Ожидание...\n");
                    continue;
                }
            }
            close(sockfd);
            close(sockmc);
        }
    }
    return 0;
}
