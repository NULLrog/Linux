#include "taxi.h"

//Taxi
Taxi* addelem_t(Taxi *head, int id, int x, int y, int sock, int status) {
    Taxi *temp, *p;
    do
        temp = malloc(sizeof(Taxi));
    while(temp == NULL);
    temp->id = id;
    temp->x = x;
    temp->y = y;
    temp->ptr = NULL;
    temp->sock = sock;
    temp->status = status;
    temp->clid = -1;
    if(head == NULL)
        return temp;
    p = head;
    while(p->ptr !=NULL)
        p = p->ptr;
    p->ptr = temp;
    return head;
}

Taxi* removel_t(Taxi *head, int sock) {
    Taxi *tmp = head, *p = NULL;
    if (head == NULL)
        return NULL;
    while (tmp->sock != sock) {
        p = tmp;
        tmp = tmp->ptr;
    }
    if (tmp == head) {
        free(head);
        return tmp->ptr;
    }
    p->ptr = tmp->ptr;
    free(tmp);
    return head;
}

Taxi* search_t(Taxi *taxis, int id) {
    while(taxis != NULL) {
        if(taxis->id == id) {
            return taxis;
        }
        taxis = taxis->ptr;
    }
    return NULL;
}

Taxi* search_t_scok(Taxi *taxis, int sock) {
    while(taxis != NULL) {
        if(taxis->sock == sock) {
            return taxis;
        }
        taxis = taxis->ptr;
    }
    return NULL;
}

Taxi* remove_all_t(Taxi *head) {
    while (head != NULL) {
        Taxi *p = head;
        head = head->ptr;
        free(p);
    }
    return NULL;
}

//Client
Client* addelem_c(Client *head, int id, int x1, int y1, int x2, int y2, int sock, int status) {
    Client *temp, *p;
    do
        temp = malloc(sizeof(Client));
    while(temp == NULL);
    temp->id = id;
    temp->x1 = x1;
    temp->y1 = y1;
    temp->x2 = x2;
    temp->y2 = y2;
    temp->ptr = NULL;
    temp->sock = sock;
    temp->taxid = -1;
    temp->status = status;
    if(head == NULL) {
        return temp;
    }

    p = head;
    while(p->ptr !=NULL)
        p = p->ptr;
    p->ptr = temp;
    return head;
}

Client* removel_c(Client *head, int sock) {
    Client *tmp = head, *p = NULL;
    if (head == NULL)
        return NULL;
    while (tmp->sock != sock) {
        p = tmp;
        tmp = tmp->ptr;
    }
    if (tmp == head) {
        free(head);
        return tmp->ptr;
    }
    p->ptr = tmp->ptr;
    free(tmp);
    return head;
}

Client* remove_all_c(Client *head) {
    while (head != NULL) {
        Client *p = head;
        head = head->ptr;
        free(p);
    }
    return NULL;
}

Client* search_c_id(Client *clients, int id) {
    while(clients != NULL) {
        if(clients->id == id) {
            return clients;
        }
        clients = clients->ptr;
    }
    return NULL;
}

//General
int distance(Taxi *taxis, Client cli) {
    int flag = 1;
    int count = 0;
    int dx, dy, answer;
    double p;
    while(taxis != NULL) {
        if(taxis->status == WAIT && flag) {
            count++;
            dx = abs(cli.x1 - taxis->x);
            dy = abs(cli.y1 - taxis->y);
            answer = taxis->id;
            p = sqrt(dx * dx + dy * dy);
            flag = 0;
        } else if(taxis->status == WAIT && !flag) {
            int dx1 = abs(cli.x1 - taxis->x);
            int dy1 = abs(cli.y1 - taxis->y);
            double p1 = sqrt(dx1 * dx1 + dy1 * dy1);
            if(p > p1) {
                dx = dx1;
                dy = dy1;
                p = p1;
                answer = taxis->id;
                count++;
            }
        }
        taxis = taxis->ptr;
    }
    if(count++)
        return answer;
    else
        return EXCEPTION;
}

double pif(int x1, int y1, int x, int y) {
    int dx = abs(x1 - x);
    int dy = abs(y1 - y);
    return sqrt(dx * dx + dy * dy)*RANDOMC;
}

int gettok(char* token) {
    token = strtok(token," ");
    return atoi(token);
}

char* getname(char* token) {
    char* tok = strtok(token," ");
    return tok;
}

int testpoints(int x, int y) {
    if(x <= 0 || x > MAPSIZE || y <= 0 || y > MAPSIZE)
        return 1;
    else
        return 0;
}

int search_taxi(Taxi *t, int sock) {
    while(t != NULL) {
        if(t->sock == sock)
            return 1;
        t = t->ptr;
    }
    return 0;
}

int search_cli(Client *t, int sock) {
    while(t != NULL) {
        if(t->sock == sock)
            return 1;
        t = t->ptr;
    }
    return 0;
}

char* getstatus(int status) {
    if(status == 0)
        return "Wait";
    else if (status == 1)
        return "Going to client";
    else if (status == 2)
        return "Waiting for client";
    else if (status == 3)
        return "On race";
    else if (status == 4)
        return "Exiting";
    else if (status == 10)
        return "Wait taxi";
    else
        return "Complete";
}

void send_stat(int sock, int status, int clid) {
    char buff[SIZE];
    memset(buff, '\0', sizeof(buff));
    snprintf (buff, sizeof(buff), "%d %d %d\n", STAT, status, clid);
    send(sock, buff, strlen(buff), 0);
}

void send_points(int sock, int x1, int y1, int x2, int y2, int status, int clid) {
    char buff[SIZE];
    memset(buff, '\0', sizeof(buff));
    snprintf (buff, sizeof(buff), "%d %d %d %d %d %d %d\n",
              STAT, status, x1, y1, x2, y2, clid);
    if((send(sock, buff, strlen(buff), 0)) == -1) {
        perror("send()");
    }
}
