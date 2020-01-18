#--- Makefile
start : client server
	./server  
	xterm ./client &
    
server : server.o
	gcc -Wall -std=c99 server.o -o server

server.o : server.c
	gcc -g -c server.c

client : client.o
	gcc -Wall -std=c99 client.o -o client

client.o : client.c
	gcc -g -c client.c
