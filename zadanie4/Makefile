#Bohdan Fedirko
CC = gcc
CFLAGS = -o
A1 ?= inp.txt
A2 ?= out.txt

all: a

a: a.c
	$(CC) $(CFLAGS) a a.c
	./a $(A1) $(A2)
	diff $(A1) $(A2)

.PHONY: a

clean:
	rm -f a


