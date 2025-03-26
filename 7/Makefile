
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: fork.o



fork.o: 
	$(CC) $(CFLAGS) -o fork.o 7.c



clean:
	rm -f fork.o

valgrind: fork.o
	valgrind --leak-check=full ./fork.o