CC=gcc
CFLAGS= -Wall -std=c99 -pedantic -g  
LIBS = -lm  -ldl -L. -ltaxi -lpthread
HEADERS = taxi.h 
EXECUTABLE = taxist client server
OBJECTS = taxist.c client.c server.c

.PHONY: clean

start : libtaxi.so $(EXECUTABLE)
	./server

$(EXECUTABLE) : % : %.o
	$(CC) $(CFLAGS) $< -o $@ $(LIBS) 
	
%.o : %.c
	$(CC) -c $<
	
libtaxi.so : taxi.o
	$(CC) -shared $< -o $@ -lm
	
taxi.o : taxi.c
	$(CC) -c -Wall -fPIC $<

clean:
	rm -f *.o $(EXECUTABLE)

