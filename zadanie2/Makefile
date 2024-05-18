CC = gcc
CFLAGS = -o

ARG ?= pid_info

all: a

a: a.c
        $(CC) $(CFLAGS) $@ $<
        $(CC) $(CFLAGS) $(ARG) $(ARG).c
        ./a $(ARG)


.PHONY: a pid_info

clean:
        rm -f a pid_info
