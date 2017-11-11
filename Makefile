
CC=gcc
AR=ar

CCFLAGS = -fPIC -Iinclude

all: liblex example1

liblex:
	$(CC) $(CCFLAGS) -c src/parser.c -o src/parser.o
	$(AR) cr liblex.a src/parser.o

example1:
	$(CC) $(CCFLAGS) -o example1 example/example1.c liblex.a

.PHONY: all example1
