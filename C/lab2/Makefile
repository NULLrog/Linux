#--- Makefile
start : lab2
	./lab2 < test.txt
lab2 : lab2.o
	gcc -Wall -std=c99 lab2.o -o lab2

lab2.o : lab2.c
	gcc -g -c lab2.c

