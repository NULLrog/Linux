#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    int num = 10;
        /* Echo message back to client */
   if (send(clntSocket, &num, sizeof(int), 0) != sizeof(int))
        DieWithError("send() failed");


    close(clntSocket);    /* Close client socket */
}
