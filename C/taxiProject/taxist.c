#include "taxi.h"

void get(char *tokcopy) {
    tokcopy = strtok (tokcopy, " ");
    while (tokcopy != NULL) {
        printf ("%s\n",tokcopy);
        fflush(stdout);
        tokcopy = strtok (NULL," ");
    }
}

int test_sock(int sockfd, fd_set fds, struct timeval tv) {
    if(select(sockfd + 1, &fds, NULL, NULL, &tv)) {
        printf("Server is down!\n");
        fflush(stdout);
        return -1;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    struct taxi t;
    int n;
    int id = getpid();
    srand(id);
    if(argc < 2) {
        printf("Usage <flag 0[with generate params]|1[for enter params]> [x] [y]\n");
        exit(-1);
    }
    if(atoi(argv[1]) == 0) {
        t.id = id;
        t.x = rand()%MAPSIZE;
        t.y = rand()%MAPSIZE;
    } else {
        if(!testpoints(atoi(argv[2]), atoi(argv[3]))) {
            t.id = id;
            t.x = atoi(argv[2]);
            t.y = atoi(argv[3]);
        } else {
            printf("Points out of range from 0 to %d\n", MAPSIZE);
            exit(-1);
        }
    }
    printf("Enter ID: %d\nx: %d\ny: %d\n",
           t.id, t.x, t.y);

    int sockfd;
    struct sockaddr_in serv_addr;
    char buff[SIZE];
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket()\n");
        exit(-1);
    }
    fd_set fds; 
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    struct timeval tv = {0, WTIME};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(ADDR);
    int i = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_QUICKACK, (void *)&i, sizeof(i));
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("connect()\n");
        exit(-1);
    }
    int tok;
    while(1) {
        memset(buff, '\0', sizeof(buff));
        if((n = recv(sockfd, &buff[0], sizeof(buff), 0)) > 0) {
            tok = gettok(buff);
            if(tok == CONNECT) {
                t.status = WAIT;
                snprintf (buff, sizeof(buff), "taxi %d %d %d %d",
                          t.id, t.x, t.y, t.status);
                send(sockfd, buff, strlen(buff), 0);
                printf("New status is %s\n", getstatus(t.status));
                fflush(stdout);
            }

            else if(tok == STAT) {
                if(gettok(NULL) == ORD) {
                    t.status = TO_CLI;
                    int x1 = gettok(NULL);
                    int y1 = gettok(NULL);
                    int x2 = gettok(NULL);
                    int y2 = gettok(NULL);
                    int clid = gettok(NULL);
                    sleep(READORDER);
                    send_stat(sockfd, t.status, clid);
                    printf("New status is %s %d\n", getstatus(t.status), clid);
                    double wtime = pif(x1, y1, t.x, t.y);
                    int percent = rand()%30;
                    wtime += wtime + wtime/100*percent;
                    printf("Time of race is %f\n", wtime);
                    sleep(wtime);
                    t.x = x1;
                    t.y = y1;
                    t.status = WAIT_CLI;
                    if(!test_sock(sockfd, fds, tv)){
                        break;
                    }
                    send_points(sockfd, x1, y1, 0, 0, t.status, clid);
                    memset(buff, '\0', sizeof(buff));
                    recv(sockfd, &buff[0], sizeof(buff), 0);
                    printf("New status is %s %d and points x=%d y=%d\n", getstatus(t.status), clid, t.x, t.y);
                    sleep(WAITINGTIME);
                    t.status = ON_RACE;
                    send_stat(sockfd, t.status, clid);
                    printf("New status is %s with client %d\n", getstatus(t.status), clid);
                    wtime = pif(x2, y2, x1, y1);
                    percent = rand()%30;
                    wtime += wtime + wtime/100*percent;
                    printf("Time of race is %f\n", wtime);
                    sleep(wtime);
                    t.x = x2;
                    t.y = y2;
                    t.status = COMPLETE;
                    printf("New status is %s\n", getstatus(t.status));
                    if(!test_sock(sockfd, fds, tv)){
                        break;
                    }
                    send_points(sockfd, x2, y2, 0, 0, t.status, clid);
                    recv(sockfd, &buff[0], sizeof(buff), 0);
                    sleep(EXITINGTIME);
                    t.status = WAIT;
                    printf("New status is %s\n", getstatus(t.status));
                    send_stat(sockfd, t.status, clid);
                } else {
                    send_stat(sockfd, ABORT, 0);
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
