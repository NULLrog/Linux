#--- Makefile	
start : liblab5_1.a lab5_1
	./lab5_1 

lab5_1 : lab5_1.o
	gcc -Wall -std=c99 lab5_1.o -L. -llab5_1 -o lab5_1 -lm 
 
lab5_1.o : lab5_1.c
	gcc -g -c lab5_1.c

liblab5_1.a : f.o
	ar rc liblab5_1.a f.o 
	ranlib liblab5_1.a
	
f.o : f.c
	gcc -c -g f.c 
	
clean:
	rm -r *.o || rm -r *.a
	
