.POSIX:

CC=gcc
BISON=bison
CFLAGS=-Werror -I. -lm
INCLUDE=foureten.h calc.tab.h calc.h
SRC=foureten.c calc.tab.c main.c
OBJ=$(SRC:.c=.o)
OUT=4e10

all : $(OUT)

*.c.o:
	$(CC) $(CFLAGS) -c $<
%.tab.h %.tab.c: %.y
	$(BISON) -d $<

debug: CFLAGS += -ggdb
debug : $(OUT)

4e10: $(INCLUDE) $(OBJ)
	$(CC) $(CFLAGS) -o 4e10 $(OBJ)

clean:
	rm -rfv $(OBJ) *.tab.*

.NOTINTERMEDIATE: calc.tab.c
.PHONY: clean
