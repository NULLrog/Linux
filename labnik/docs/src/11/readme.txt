Example code:
	TCPEchoClient.c
	DieWithError.c
	TCPEchoServer.c
	HandleTCPClient.c
	UDPEchoClient.c
	UDPEchoServer.c
	SigAction.c
	UDPEchoServer-SIGIO.c
	UDPEchoClient-Timeout.c
	TCPEchoServer-Fork.c (without SIGCHLD)
	TCPEchoServer-Fork-SIGCHLD.c (with SIGCHLD)
	TCPEchoServer.h
	CreateTCPServerSocket.c
	AcceptTCPConnection.c
	TCPEchoServer-Thread.c
	TCPEchoServer-ForkN.c
	TCPEchoServer-Select.c
	BroadcastSender.c
	BroadcastReceiver.c
	MulticastSender.c
	MulticastReceiver.c
	ResolveName.c
	ResolveService.c

Generally, compilation is as follows:
	Linux: gcc -o TCPEchoClient TCPEchoClient.c DieWithError.c
	Solaris: gcc -o TCPEchoClient TCPEchoClient.c DieWithError.c -lsocket -lnsl
	Both: Add -lpthread to both Linux and Solaris for the threads example

Note for older machines (e.g., SVR4 variants such as Solaris 2.5 and before): 
A few more include files may be necessary. If you get compile errors about u_short, try editing the include files as follows (order matters):
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/types.h>  /* for Socket data types */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <netinet/in.h> /* for IP Socket data types */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

