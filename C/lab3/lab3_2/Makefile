#--- Makefile
start : lab3_2
	./lab3_2 < test.txt
lab3_2 : lab3_2.o
	gcc -Wall -std=c99 lab3_2.o -o lab3_2

lab3_2.o : lab3_2.c
	gcc -c -g lab3_2.c

