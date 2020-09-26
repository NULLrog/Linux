#include <stdio.h>
#include "mymsg.h"
int main(int argc, char **argv){
	int msgqid, rc;
	
	msgqid = msgget(MSGKEY, MSGPERM|IPC_EXCL);
	if (msgqid < 0) {
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		return 1;
	} else 
		printf("message queue %d created\n", msgqid);
	// read the message from queue
	rc = msgrcv(msgqid, &msg, sizeof(msg)-sizeof(long), 0, 0); 
	if (rc < 0) {
		perror( strerror(errno) );
		printf("msgrcv failed, rc=%d\n", rc);
		return 1;
	} 
	printf("received msg: %s\n", msg.mtext);
	printf("received len: %d\n", msg.len);

	// remove the queue
	rc=msgctl(msgqid,IPC_RMID,NULL);
	if (rc < 0) {
		perror( strerror(errno) );
		printf("msgctl (return queue) failed, rc=%d\n", rc);
		return 1;
	}
	printf("message queue %d is gone\n",msgqid);	
	return 0;
}

