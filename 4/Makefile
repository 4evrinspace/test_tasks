
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: args.o



args.o: 
	$(CC) $(CFLAGS) -o args.o 4.c



clean:
	rm -f args.o


valgrind: args.o
	valgrind --leak-check=full ./args.o