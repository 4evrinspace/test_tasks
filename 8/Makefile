
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: sigaction.o signal.o



%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f *.o
