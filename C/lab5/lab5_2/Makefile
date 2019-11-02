#--- Makefile	
start : liblab5_2.so lab5_2 
	./lab5_2

lab5_2 : lab5_2.o
	gcc -Wall -std=c99 lab5_2.o -L. -llab5_2 -o lab5_2 -lm -ldl

lab5_2.o : lab5_2.c
	gcc -g -c lab5_2.c

liblab5_2.so : f.o
	gcc -shared -o liblab5_2.so f.o -lm

f.o : f.c
	gcc -c -fPIC f.c 

clean:
	rm -r *.o || rm -r *.a
