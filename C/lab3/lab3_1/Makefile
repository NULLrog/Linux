#--- Makefile
start : lab3_1
	./lab3_1 < test.txt
lab3_1 : lab3_1.o
	gcc -Wall -std=c99 lab3_1.o -o lab3_1

lab3_1.o : lab3_1.c
	gcc -g -c lab3_1.c

