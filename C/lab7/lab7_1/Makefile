#--- Makefile
start : lab7_1 
	./lab7_1 lab7_1.c lab7_1.o Makefile
lab7_1 : lab7_1.o
	gcc -Wall -std=c99 lab7_1.o -o lab7_1

lab7_1.o : lab7_1.c
	gcc -g -c lab7_1.c
