CC=gcc
CFLAGS=-Wall -I.
DEPS=solver.h bfs.h combinatorics.h bit_manip_bytes_to_str.h polish_n.h
SHROBJS=-lclhash

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

solvermake : solver.c pn.c
	$(CC) -o solver solver.c pn.c $(CFLAGS)

bitmanip : bit_manip_bytes_to_str.c pn.c
	$(CC) -o bit_manip manip.c bit_manip_bytes_to_str.c pn.c combinatorics.c $(CFLAGS)

search : bfs.c pn.c bit_manip_bytes_to_str.c combinatorics.c
	$(CC) -o test main.c bfs.c pn.c bit_manip_bytes_to_str.c combinatorics.c $(CFLAGS) $(SHROBJS)
