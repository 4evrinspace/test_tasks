
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: numbers.o



numbers.o: 
	$(CC) $(CFLAGS) -o numbers.o 9.c



clean:
	rm -f numbers.o

valgrind: numbers.o
	valgrind --leak-check=full ./numbers.o