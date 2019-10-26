#--- Makefile
start : lab4_2
	./lab4_2 test.txt 4
lab4_2 : lab4_2.o
	gcc -Wall -std=c99 lab4_2.o -o lab4_2

lab4_2.o : lab4_2.c
	gcc -g -c lab4_2.c

