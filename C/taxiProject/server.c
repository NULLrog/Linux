#include "taxi.h"

int sockfd, newsockfd;

Taxi *taxis = NULL;
Client *clients = NULL;
Client *clihead = NULL;
Taxi *head = NULL;

int TAXICOUNT = 0;
int CLICOUNT = 0;
int THREADCOUNT = 0;

struct {
	pthread_mutex_t	mutex;
	Res *res;
} 
shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

sigset_t new_mask;
sigset_t old_mask;

void info() {
	printf("Now work %d taxis and %d clients\n", TAXICOUNT, CLICOUNT);
}

void handle_sigusr(int sig) {
	info();
}

void handle_sigterm(int sig) {
    printf("\nBuy!");
    taxis = remove_all_t(taxis);
    clients = remove_all_c(clients);
    close(sockfd);
    close(newsockfd);
    exit(0);
}

void* distance(void* arg) {
    while (taxis != NULL) {
        int id;
        int flag = 1; 
        pthread_mutex_lock(&shared.mutex);
        int dx = abs(clients->x1 - taxis->x);
        int dy = abs(clients->y1- taxis->y);
        id = taxis->id;
        if(taxis->clid != -1)
            flag = 0;
        taxis = taxis->ptr;
        pthread_mutex_unlock(&shared.mutex);
	    double d = (sqrt(dx * dx + dy * dy));
        sleep(WAITINGTIME);
        pthread_mutex_lock(&shared.mutex);
        if(flag)
            shared.res = addelem_res(shared.res, id, d);
        flag = 1;
        //printf("Res of thread is %f for taxi %d\n", shared.res->dist, shared.res->idtax);
        pthread_mutex_unlock(&shared.mutex);
        srand(getpid());
        usleep(rand()%MAPSIZE);
    }
    pthread_exit(NULL);
}

void race(Taxi *taxis, Client *clients) {
    char buff[SIZE];
    int tok;
    memset(buff, '\0', sizeof(buff));
    send_points(taxis->sock, clients->x1, clients->y1,  clients->x2, clients->y2, ORD, clients->id);
    taxis->clid = clients->id;
}

void pnt(int status, int sd, int tok) {
    taxis = search_t_scok(taxis, sd);
    taxis->x = gettok(NULL);
    taxis->y = gettok(NULL);
    gettok(NULL);
    gettok(NULL);
    taxis->status = tok;
    int clid = gettok(NULL);
    clients = search_c_id(clients, clid);
    if(clients!=NULL) {
        send(taxis->sock, "OK", 2, 0);
        clients->status = status;
        send_stat(clients->sock, clients->status, clients->taxid);
        printf("Taxi %d %s %d, new point is x=%d y=%d!\n", taxis->id, getstatus(taxis->status), clid, taxis->x, taxis->y);
    }
    else {
        send(taxis->sock, "GONE", 4, 0);
        if(status == COMPLETE)
            printf("Taxi %d %s %d, new point is x=%d y=%d!\n", taxis->id, getstatus(taxis->status), clid, taxis->x, taxis->y);
        else
            printf("Taxi %d stop, client is gone, new point is x=%d y=%d!\n", taxis->id, taxis->x, taxis->y);
        taxis->status = WAIT;
        taxis->clid = -1;
    }
    clients = clihead;
    taxis = head;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigterm);
    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR1, handle_sigusr);
    signal(SIGUSR2, handle_sigusr);
    sigprocmask(SIG_SETMASK, &new_mask, &old_mask);
    int client_socket[CLIMAX];
    int activity, sd;
    int max_sd;
    fd_set readfds;
    fd_set readin;
    struct timeval tv = {1, 0};
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char *stat;
    pthread_t threads[CORES];
    int flags = 0;
    int n;
    int first_t = 0;
    int first_c = 0;
    char buff[SIZE];
    
    char message[SIZE];
    snprintf (message, sizeof(message), "%d Connect for server\n", CONNECT);
    printf("server starting\n");
    fflush(stdout);

    for (int i =0 ; i <  CLIMAX; i++) {
        client_socket[i] = 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()\n");
        exit(-1);
    }

    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_QUICKACK, (void *)&flag, sizeof(flag));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flag, sizeof(flag));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind()\n");
        exit(-1);
    }
    listen(sockfd, CLIMAX);
    clilen = sizeof(cli_addr);
    char * token;
    while (1) {
        FD_ZERO(&readin);
        FD_SET(STDIN, &readin);

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;
        for (int i = 0 ; i < CLIMAX; i++) {
            sd = client_socket[i];
            if(sd > 0)
                FD_SET(sd, &readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        if(select(STDIN + 1, &readin, NULL, NULL, &tv)) {
            if(getchar())
                info();
        }

        select( max_sd + 1, &readfds, NULL, NULL, &tv);

        if (FD_ISSET(sockfd, &readfds)) {
            if ((newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen))<0) {
                perror("accept()\n");
                exit(-1);
            }
            send(newsockfd, message, sizeof(message), 0);
            for (int i = 0; i < CLIMAX; i++) {
                if( client_socket[i] == 0 ) {
                    client_socket[i] = newsockfd;
                    break;
                }
            }
        }

        for (int i = 0; i < CLIMAX; i++) {
            sd = client_socket[i];
            memset(buff, 0, sizeof(buff));
            if (FD_ISSET(sd, &readfds)) {
                if ((n = recv(sd, &buff[0], sizeof(buff), 0)) == 0) { 
                    printf("Sock %d disconnected\n", sd);
                    fflush(stdout);
                    close(sd);
                    client_socket[i] = 0;
                    clihead = clients;
                    head = taxis;
                    if(search_taxi(taxis, sd)) {
                        flags = 0;
                        taxis = search_t_scok(taxis, sd);
                        if(taxis->clid != -1) {
                            if((clients = search_c_id(clients, taxis->clid))) {
                                send_stat(clients->sock, ABORT, 0);
                                flags = 1;
                                TAXICOUNT--;
                                taxis = head;
                                taxis = removel_t(taxis, sd);                                
                                if(TAXICOUNT) {  
                                    for (int i = 0; i < CORES; i++) {
                                        pthread_create(&threads[i], NULL, distance, NULL);
                                    }
                                    int temptreads = CORES;
                                    for (int i = 0; i < CORES; i++) {
                                        pthread_join(threads[i], NULL);
                                    }     
                                    taxis = head;
                                    if(shared.res == NULL) {
                                        clients->taxid = -1;
                                        clients->status = WAIT;
                                        clients = clihead;
                                        continue;
                                    }
                                    int selected = shared.res->idtax;
                                    int mindist = shared.res->dist;
                                    shared.res = shared.res->ptr;
                                    while(shared.res) {
                                        if(mindist > shared.res->dist) {
                                            selected = shared.res->idtax;
                                            mindist = shared.res->dist;
                                        }
                                        shared.res = shared.res->ptr;
                                    }
                                    taxis = search_t(taxis, selected);

                                    clients->taxid = taxis->id;
                                    taxis->clid = clients->id;
                                    clients->status = WAIT;
                                    send_stat(clients->sock, clients->status, clients->taxid);
                                    race(taxis, clients);
                                    clients = clihead;
                                    taxis = head;
                                    shared.res = remove_all_r(shared.res);
                                } 
                            }
                        }
                        clients = clihead;
                        if(!flags){
                            TAXICOUNT--;
                            taxis = head;
                            taxis = removel_t(taxis, sd);
                        } 
                    }
                    clients = clihead;
                    if(search_cli(clients, sd)) {
                        CLICOUNT--;
                        clients = removel_c(clients, sd);
                        clihead = clients;
                        sleep(EXITINGTIME);
                    }
                } else {
                    buff[n] = '\0';
                    char *token = strtok (buff, " ");
                    if(strcmp(token, "taxi") == 0) {
                        Taxi t;
                        t.id = gettok(NULL);
                        t.x = gettok(NULL);
                        t.y = gettok(NULL);
                        t.sock = sd;
                        t.status = gettok(NULL);
                        printf("taxi %d, socket %d, points x=%d y=%d\n", t.id, sd, t.x, t.y);
                        taxis = addelem_t(taxis, t.id, t.x, t.y, t.sock, t.status);
                        head = taxis;
                        taxis = search_t(taxis, t.id);
                        TAXICOUNT++;
                        strcpy(buff, "Waiting for client");
                        memset(buff, 0, sizeof(buff));
                        clihead = clients;
                        while(clients!=NULL) {
                            if(clients->taxid == -1) {
                                clients->taxid = taxis->id;
                                taxis->clid = clients->id;
                                race(taxis, clients);
                                send_stat(clients->sock, clients->status, clients->taxid);
                                break;
                            }
                            clients = clients->ptr;
                        }
                        taxis = head;
                        clients = clihead;
                    } else if(strcmp(token, "client") == 0) {
                        Client cli;
                        cli.id = gettok(NULL);
                        cli.x1 = gettok(NULL);
                        cli.y1 = gettok(NULL);
                        cli.x2 = gettok(NULL);
                        cli.y2 = gettok(NULL);
                        cli.status = WAIT;
                        cli.sock = sd;
                        clients = addelem_c(clients, cli.id, cli.x1, cli.y1, cli.x2, cli.y2, sd, cli.status);
                        CLICOUNT++;
                        clihead = clients;
                        printf("client %d from x1=%d y1=%d to x2=%d y2=%d\n",
                               cli.id, cli.x1, cli.y1, cli.x2, cli.y2);
                        if(TAXICOUNT) {
                            for (int i = 0; i < CORES; i++) {
                                pthread_create(&threads[i], NULL, distance, NULL);
                            }
                            int temptreads = CORES;
                            for (int i = 0; i < CORES; i++) {
                                pthread_join(threads[i], NULL);
                            }     
                            taxis = head;
                            if(shared.res == NULL)
                                continue;
                            int selected = shared.res->idtax;
                            int mindist = shared.res->dist;
                            shared.res = shared.res->ptr;
                            while(shared.res) {
                                if(mindist > shared.res->dist) {
                                    selected = shared.res->idtax;
                                    mindist = shared.res->dist;
                                }
                                shared.res = shared.res->ptr;
                            }
                            taxis = search_t(taxis, selected);
                            clients = search_c_id(clients, cli.id);
                            clients->taxid = taxis->id;
                            taxis->clid = clients->id;
                            clients->status = WAIT;
                            send_stat(clients->sock, clients->status, clients->taxid);
                            race(taxis, clients);
                            clients = clihead;
                            taxis = head;
                            shared.res = remove_all_r(shared.res);
                        } else {
                            send_stat(cli.sock, cli.status, 0);
                        }
                    } else if(atoi(token) == STAT) {
                        int tok = gettok(NULL);
                        if(tok == TO_CLI) {
                            taxis = search_t_scok(taxis, sd);
                            taxis->status = tok;
                            int clid = gettok(NULL);
                            printf("Taxi %d %s %d!\n", taxis->id, getstatus(taxis->status), clid);
                            clients = clihead;
                            taxis = head;
                        } else if(tok == WAIT_CLI) {
                            pnt(EXITING, sd, tok);
                        } else if(tok == ON_RACE) {
                            taxis = search_t_scok(taxis, sd);
                            taxis->status = tok;
                            int clid = gettok(NULL);
                            clients = search_c_id(clients, clid);
                            if(clients != NULL) {
                                clients->status = ON_RACE;
                                send_stat(clients->sock, clients->status, clients->taxid);
                            }
                            printf("Taxi %d %s %d!\n", taxis->id, getstatus(taxis->status), clid);
                            clients = clihead;
                            taxis = head;
                        } else if(tok == COMPLETE) {
                            pnt(COMPLETE, sd, tok);
                        } else if(tok == WAIT) {
                            taxis = search_t_scok(taxis, sd);
                            taxis->status = tok;
                            int clid = gettok(NULL);
                            printf("Taxi %d %s!\n", taxis->id, getstatus(taxis->status));
                            while(clients != NULL ) {
                                if(clients->taxid == -1) {
                                    clients->taxid = taxis->id;
                                    taxis->clid = clients->id;
                                    send_stat(clients->sock, clients->status, clients->taxid);
                                    race(taxis, clients);
                                    break;
                                }
                                clients = clients->ptr;
                            }
                            taxis->clid = -1;
                            clients = clihead;
                            taxis = head;
                        }
                        memset(buff, 0, sizeof(buff));
                    }
                }
            }
        }
    }
    return(0);
}
