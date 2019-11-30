#ifndef __WARCRAFT_H__
#define __WARCRAFT_H__

#include<sys/ipc.h>
#include<sys/msg.h>

struct mymsgbuf {
	long mtype;
	int number;
};
#endif
