#--- Makefile
start : lab6_1 
	./lab6_1 lab6_1.c lab6_1.o Makefile
lab6_1 : lab6_1.o
	gcc -Wall -std=c99 lab6_1.o -o lab6_1

lab6_1.o : lab6_1.c
	gcc -g -c lab6_1.c

