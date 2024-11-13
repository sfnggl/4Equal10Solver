.POSIX:

CC=gcc
CFLAGS=-Wall -Werror -I.
INCLUDE=foureten.h
SRC=main.c
OBJ=$(SRC:.c=.o)
OUT=4e10

all : $(OUT)

*.c.o: $(CC) $(CFLAGS) -c $<

debug: CFLAGS += -ggdb
debug : $(OUT)

4e10: $(INCLUDE) $(OBJ)
	$(CC) $(CFLAGS) -o 4e10 $(OBJ)

clean:
	rm -rfv $(OBJ) $(OUT)

.PHONY: clean
