#--- Makefile
start : server client1 client2 
	./start.sh
server : server.o
	gcc -Wall -std=c99 server.o -o server

server.o : server.c
	gcc -g -c server.c

client2 : client2.o
	gcc -Wall -std=c99 client2.o -o client2

client2.o : client2.c
	gcc -g -c client2.c
	
client1 : client1.o
	gcc -Wall -std=c99 client1.o -o client1

client1.o : client1.c
	gcc -g -c client1.c
