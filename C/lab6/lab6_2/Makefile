#--- Makefile
start : file lab6_2 
	./lab6_2 lab6_2.c lab6_2.o Makefile
lab6_2 : lab6_2.o
	gcc -Wall -std=c99 lab6_2.o -o lab6_2

lab6_2.o : lab6_2.c
	gcc -g -c lab6_2.c
	

	
file.o : file.c
	gcc -g -c file.c

file : file.o	
	gcc -Wall -std=c99 file.o -o file
