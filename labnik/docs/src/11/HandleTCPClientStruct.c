#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <unistd.h>     /* for close() */
#include "protocol.h"  

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */

    struct protocol proto;
    if ((recvMsgSize = recv(clntSocket, &proto, sizeof(proto), 0)) < 0)
      DieWithError("recv() failed");
    
    printf("time=%d", proto.time);  
	printf("size=%d", proto.len);
	
   if ((recvMsgSize = recv(clntSocket, echoBuffer, proto.len, 0)) < 0)
      DieWithError("recv() failed");
    echoBuffer[proto.len] = '\0';  
    printf("str=%s", echoBuffer);  
	printf("\n");  
    fflush(stdout);
    close(clntSocket);    /* Close client socket */
}
