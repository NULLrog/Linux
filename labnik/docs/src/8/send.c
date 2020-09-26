#include <stdio.h>
#include "mymsg.h"
#include <sys/types.h>
#include <unistd.h>

int get_queue_ds( int qid, struct msqid_ds *qbuf ){
	if( msgctl( qid, IPC_STAT, qbuf) == -1){
                return(-1);
    }
    return(0);
}

int main(int argc, char **argv){
	int msgqid, rc;
	msgqid = msgget(MSGKEY, MSGPERM|IPC_CREAT|IPC_EXCL);
	if (msgqid < 0) {
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		return 1;
	} else 
		printf("message queue %d created\n",msgqid);

	// message to send
	msg.mtype = 1; // set the type of message
	msg.len = sizeof(msg)-sizeof(long);//getpid();
	sprintf (msg.mtext, "%s\n", "a text msg..."); 
	printf ("a len msg = %d\n", msg.len); 

	// send the message to queue
	rc = msgsnd(msgqid, &msg, sizeof(msg)-sizeof(long), 0); 
	// the last param can be: 0, IPC_NOWAIT, MSG_NOERROR, or IPC_NOWAIT|MSG_NOERROR.
	if (rc < 0) {
		perror( strerror(errno) );
		printf("msgsnd failed, rc = %d\n", rc);
		return 1;
	} else
		printf("Message send done!\n");
		
	return 0;
}
