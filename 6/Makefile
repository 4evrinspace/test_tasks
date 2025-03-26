
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: stat.o



stat.o: 
	$(CC) $(CFLAGS) -o stat.o 6.c



clean:
	rm -f stat.o

valgrind: stat.o
	valgrind --leak-check=full ./stat.o