#Bohdan Fedirko
CC = gcc
CFLAGS = -o
PEDANTIC = -Wall -std=c99 -pedantic
LIB = sem_handlers
A ?= prog
B ?= 5
C ?= 1

all: a

a: a.c

        $(CC) $(PEDANTIC) -c $(LIB).c $(CFLAGS) $(LIB).o
        $(CC) $(PEDANTIC) prog.c $(CFLAGS) prog $(LIB).c
        $(CC) $(PEDANTIC) a.c $(CFLAGS) a $(LIB).c


        ./a $(A) $(B) $(C)

.PHONY: a

clean:
        rm -f a prog
