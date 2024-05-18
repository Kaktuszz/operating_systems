#Bohdan Fedirko
CC = gcc
CFLAGS = -o
X = xterm
XFLAGS = -hold -title
PIPE = mkfifo
A ?= buf
B ?= inp.txt
C ?= out.txt

all: a b

a: a.c
        $(CC) $(CFLAGS) prod prod.c
        $(CC) $(CFLAGS) kons kons.c
        $(CC) $(CFLAGS) a a.c
        ./a $(A) $(B) $(C)
        diff $(B) $(C)
b:
        $(PIPE) $(A)
        $(CC) $(CFLAGS) prod prod.c
        $(CC) $(CFLAGS) kons kons.c
        $(X) $(XFLAGS) prod_term -e ./prod $(A) $(B) $(C) & ./kons $(A) $(B) $(C)
        rm $(A)
        diff $(B) $(C)

.PHONY: a b

clean:
        rm -f a kons prod
