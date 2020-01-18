#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define PORT 12345
#define ADR "127.0.0.1"
#define MSG_MAX 10
#define BUFSIZE 256

int *shm;
int shmid;

struct mymsgbuf {
    long mtype;
    char mtext[BUFSIZE];
};


void attach() {
    if ((shm = (int *)shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("Не удалось получить доступ к разделяемой памяти!\n");
        exit(-4);
    }
}

void detach() {
    if (shmdt(shm) < 0) {
        printf("Ошибка отключения\n");
        exit(-5);
    }
}

void send_message(int qid, struct mymsgbuf *qbuf, char *text) {
    qbuf->mtype = 1;
    strcpy(qbuf->mtext, text);
    if ((msgsnd(qid, (struct msgbuf *)qbuf, strlen(qbuf->mtext) + 1, 0)) == -1) {
        perror("msgsnd");
    }
}

void read_message(int qid, struct mymsgbuf *qbuf, char *msg) {
    qbuf->mtype = 1;
    msgrcv(qid, (struct msgbuf *)qbuf, BUFSIZE, 1, 0);
    strcpy(msg, qbuf->mtext);
}

int main(int argc, char *argv[]) {
    printf("СЕРВЕР: Начало работы\n");
    struct sockaddr_in serv_addr;
    int mcPort = 10000;
    key_t key;
    key = ftok(".", 'm');
    int msgqid;
    if ((msgqid = msgget(key, IPC_CREAT | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }
    struct mymsgbuf qbuf;
    if ((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("Не удалось создать область разделяемой памяти!\n");
        exit(-3);
    }
    attach();
    *shm = 0;
    detach();
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);
    char buf[BUFSIZE];
    sprintf(buf, "%d", mcPort);
    int pid=fork();
    if (pid == -1) {
        perror("Ошибка создания юнита");
        exit(-3);
    } else if (pid == 0) {
        int sock;
        int cc;
        struct sockaddr_in multicast_addr[100];
        char echobuf2[BUFSIZE];
        if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
            perror("socket()");
        for (int i = 0; i < 100; i++) {
            memset(&multicast_addr[i], 0, sizeof (multicast_addr[i]));
            multicast_addr[i].sin_family = AF_INET;
            multicast_addr[i].sin_addr.s_addr = INADDR_ANY;
            multicast_addr[i].sin_port = htons(mcPort + i);
        }
        while(1) {
            attach();
            cc = *shm;
            detach();
            //printf("Special read:%d\n",cc);
            for (int i = 0; i < 100; i++) {
                if (cc < MSG_MAX) {
                    strcpy(echobuf2, "Пиши");
                    sendto(sock, echobuf2, strlen(echobuf2), 0, (struct sockaddr *)&multicast_addr[i], sizeof(multicast_addr[i]));
                }
                if (cc > 0) {
                    strcpy(echobuf2,"Читай");
                    sendto(sock, echobuf2, strlen(echobuf2), 0, (struct sockaddr *)&multicast_addr[i], sizeof(multicast_addr[i]));
                }
            }
            sleep(1);
        }
        exit(0);
    }

    while (1) {
        int connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        if (mcPort == 8000)
            mcPort = 8100;
        sprintf(buf, "%d", mcPort);
        write(connfd, buf, strlen(buf));
        mcPort++;
        pid = fork();
        if (pid < 0)
            exit(-1);
        if (pid == 0) {
            char info[1];
            read(connfd, info, sizeof (info));
            attach();
            if (strcmp(info, "1") == 0) {
                if (*shm < MSG_MAX) {
                    recv(connfd, buf, sizeof(buf), 0);
                    buf[10] = '\0';
                    int tmp = *shm + 1;
                    *shm = tmp;
                    printf("%d)Сообщение получено: %s\n", *shm, buf);
                    send_message(msgqid, (struct mymsgbuf *)&qbuf, buf);
                    detach();
                    sleep(1);
                    exit(0);
                }
            }
            if (strcmp(info, "2") == 0) {
                if (*shm > 0) {
                    read_message(msgqid, (struct mymsgbuf *)&qbuf, buf);
                    send(connfd, buf, strlen(buf), 0);
                    printf("%d)Сообщение отправлено: %s\n", *shm, buf);
                    int tmp = *shm - 1;
                    *shm = tmp;
                    detach();
                    sleep(1);
                    exit(0);
                }
            }
        }
    }
    return 0;
}
