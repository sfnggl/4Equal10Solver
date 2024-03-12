CC=gcc
CFLAGS=-Wall -I.
DEPS=solver.h

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

solvermake : solver.c tree.c
	gcc -o solver solver.c tree.c $(CFLAGS)
