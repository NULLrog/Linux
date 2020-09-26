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
#include <math.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <signal.h>

#ifndef TAXI_H
#define TAXI_H

#define SIZE 1024
#define PORT 12345
#define ADDR "127.0.0.1"
#define CLIMAX 10
#define MAPSIZE 1000

#define STDIN 0

#define WAITINGTIME 2
#define EXITINGTIME 1
#define READORDER 1
#define ACCEPTPLACE 1

#define WAIT 0
#define TO_CLI 1
#define WAIT_CLI 2
#define ON_RACE 3
#define EXITING 4
#define COMPLETE 5
#define CONNECT 6
#define ORD 7
#define WAIT_TAXI 10
#define ABORT -1
#define EXCEPTION -100

#define POINTS 4
#define STAT 5

#define RANDOMC 0.2

#define WTIME 0.1

struct taxi {
    int id, x, y, sock, status, clid;
    struct taxi *ptr;
} typedef Taxi;

struct client {
    int id, x1, y1, x2, y2, sock, status, taxid;
    struct client *ptr;
} typedef Client;

Taxi* search_t(Taxi *taxis, int id);
Taxi* removel_t(Taxi *head, int sock);
Taxi* remove_all_t(Taxi *head);
Taxi* addelem_t(Taxi *head, int id, int x, int y, int sock, int status);
Taxi* search_t_scok(Taxi *taxis, int sock);
char* getstatus(int status);
Client* removel_c(Client *head, int sock);
Client* remove_all_c(Client *head);
Client* addelem_c(Client *head, int id, int x1, int y1, int x2, int y2, int sock, int status);
Client* search_c_id(Client *clients, int sock);
int distance(Taxi *taxis, Client cli);
int gettok(char* token);
int testpoints(int x, int y);
int search_taxi(Taxi *t, int sock);
int search_cli(Client *t, int sock);
char* getname(char* token);
double pif(int x1, int y1, int x, int y);
void send_points(int sock, int x1, int y1, int x2, int y2, int status, int clid);
void send_stat(int sock, int status, int clid);

#endif
