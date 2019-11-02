#--- Makefile
start : lab4_1
	./lab4_1 test.txt 4
	
lab4_1 : lab4_1.o
	gcc -Wall -std=c99 lab4_1.o -o lab4_1

lab4_1.o : lab4_1.c
	gcc -g -c lab4_1.c
