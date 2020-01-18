#--- Makefile
start : lab9 
	./lab9 6
lab9 : lab9.o
	gcc -Wall -std=c99 lab9.o -o lab9

lab9.o : lab9.c
	gcc -g -c lab9.c
