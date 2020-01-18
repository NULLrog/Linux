#--- Makefile
start : lab10 
	./lab10 5
lab10 : lab10.o
	gcc -Wall -std=c99 lab10.o -o lab10 -lpthread

lab10.o : lab10.c
	gcc -g -c lab10.c
