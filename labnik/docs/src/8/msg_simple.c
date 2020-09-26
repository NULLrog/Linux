#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
struct msgbuf {
		long mtype; /* тип сообщения, должен быть > О */ 
		char mtext[1]; /* данные */
	};
int main(int argc, char **argv){
	int msqid, n;
	struct msqid_ds info;
	struct msgbuf buf;
	msqid = msgget(IPC_PRIVATE, 0600|IPC_CREAT);
	buf.mtype = 1;
	buf.mtext[0] = 'A';
	msgsnd(msqid, &buf, 1, 0);
	msgctl(msqid, IPC_STAT, &info);
	printf("read-write: %o, cbytes = %lu, qnum = %lu, qbytes =%lu\n", 
		(ulong)info.msg_perm.mode, (ulong) info.msg_cbytes,
		(ulong) info.msg_qnum, (ulong) info.msg_qbytes);
		
	n = msgrcv(msqid, &buf, 1, buf.mtype, IPC_NOWAIT);
	printf("read %d bytes, type=%ld : %c\n",n,buf.mtype,buf.mtext[0]);
	msgctl(msqid, IPC_RMID, NULL);
	return 0;
}

