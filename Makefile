# This is a comment line
CC=gcc
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -Wall -g

all: prog

prog: main.o doubly_linked.o single_linked.o
	$(CC) main.o doubly_linked.o single_linked.o -o prog

doubly_linked.o: doubly_linked.c
	$(CC) $(CFLAGS) doubly_linked.c

single_linked.o: single_linked.c
	$(CC) $(CFLAGS) single_linked.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o prog *.h.gch