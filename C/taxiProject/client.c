#include "taxi.h"

int main(int argc, char *argv[]) {
    struct client cli;
    int n;
    int id = getpid();
    srand(id);
    if(argc < 2) {
        printf("Usage <flag 0[with generate params]|1[for enter params]> [x1] [x2] [y1] [y2]\n");
        exit(-1);
    }
    if(atoi(argv[1]) == 0) {
        cli.id = id;
        cli.x1 = rand()%MAPSIZE;
        cli.y1 = rand()%MAPSIZE;
        cli.x2 = rand()%MAPSIZE;
        cli.y2 = rand()%MAPSIZE;
    } else {
        if(!testpoints(atoi(argv[2]), atoi(argv[3])) ||
                !testpoints(atoi(argv[4]), atoi(argv[5]))) {
            cli.id = id;
            cli.x1 = atoi(argv[2]);
            cli.y1 = atoi(argv[3]);
            cli.x2 = atoi(argv[4]);
            cli.y2 = atoi(argv[5]);
        } else {
            printf("Points out of range from 0 to %d\n", MAPSIZE);
            exit(-1);
        }

    }
    printf("Enter ID: %d\nx1: %d\ny1: %d\nx2: %d\ny2: %d\n",
           cli.id, cli.x1, cli.y1, cli.x2, cli.y2);

    int sockfd;
    struct sockaddr_in serv_addr;
    char buff[SIZE];
    printf("client starting\n");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket()\n");
        exit(-1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(ADDR);
    int i = 1;
    setsockopt( sockfd, IPPROTO_TCP, TCP_QUICKACK, (void *)&i, sizeof(i));
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("connect()\n");
        exit(-1);
    }
    int tok;
    while(1) {
        memset(buff, '\0', sizeof(buff));
        if((n = recv(sockfd, &buff[0], sizeof(buff), 0)) > 0) {
            tok = gettok(buff);
            if(tok == CONNECT) {
                snprintf (buff, sizeof(buff), "client %d %d %d %d %d",
                          cli.id, cli.x1, cli.y1, cli.x2, cli.y2);
                send(sockfd, buff, strlen(buff), 0);
            }

            else if(tok == STAT) {
                int status = gettok(NULL);
                if(status == COMPLETE) {
                    printf("Trip to x=%d y=%d is complete\n", cli.x1, cli.y1);
                    break;
                }
                if(status == ABORT) {
                    printf("Taxist died, search new taxi!\n");
                    cli.status = WAIT;
                    continue;
                } else {
                    cli.status = status;
                    if(status == WAIT)
                        cli.taxid = gettok(NULL);
                    if(cli.taxid == 0 && status == WAIT)
                        printf("New status is %s, but taxists not exists on line!\n", getstatus(cli.status));
                    else
                        printf("New status is %s, taxi is %d\n", getstatus(cli.status), cli.taxid);
                }
            }
        } else {
            printf("Server is down!\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
