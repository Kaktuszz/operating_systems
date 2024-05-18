#Bohdan Fedirko
CC = gcc
CFLAGS = -o
A1 ?=
A2 ?=

all: a b c

a: a.c
	$(CC) $(CFLAGS) a a.c
	./a $(A1) $(A2)

b: b.c
	$(CC) $(CFLAGS) b b.c
	$(CC) $(CFLAGS) a a.c
	./b $(A1) $(A2)

c: c.c
	$(CC) $(CFLAGS) c c.c
	$(CC) $(CFLAGS) c_1 c_1.c
	$(CC) $(CFLAGS) a a.c
	./c $(A1) $(A2)


.PHONY: a b c c_1

clean:
	rm -f a b c c_1


