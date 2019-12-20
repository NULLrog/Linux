#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int my_sock, n;
    int entered = 0;
    struct sockaddr_in serv_addr;

    char buff[1024];
    printf("КЛИЕНТ: начало работы\n");
    if ((my_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Ошибка открытия сокета!\n");
        exit(-1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(my_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("Ошибка соединения!\n");
        exit(-2);
    }

    while ((n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) > 0) {
        buff[n] = '\0';
        printf("СЕРВЕР:%s\n", buff);
        if(entered == 0) {
            fgets(&buff[0], sizeof(buff) - 1, stdin);
            entered = 1;
            send(my_sock, &buff[0], strlen(&buff[0]), 0);
        }  
    }
    close(my_sock);
    return 0;
}
