#ifndef __MYMSG_H__
#define __MYMSG_H__

#include<string.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/errno.h>

#define MSGPERM 0600    // msg queue permission
#define MSGTXTLEN 128   // msg text length
#define MSGKEY 32769
struct msg_buf {
  long mtype;
  char mtext[MSGTXTLEN];
  int len;
} msg;
#endif
