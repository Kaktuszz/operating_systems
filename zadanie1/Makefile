# Bohdan Fedirko
CC = gcc
CFLAGS = -o

all: a b c d e

a: a.c
	$(CC) $(CFLAGS) a a.c
	./a

b: b.c
	$(CC) $(CFLAGS) b b.c
	./b

c: c.c
	$(CC) $(CFLAGS) c c.c
	./c

d: d.c
	$(CC) $(CFLAGS) d d.c
	./d

e: e.c
	$(CC) $(CFLAGS) e e.c
	./e

.PHONY: a b c d e

clean:
	rm -f a b c d d.txt


