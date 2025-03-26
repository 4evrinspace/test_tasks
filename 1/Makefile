
CC = gcc
CFLAGS = -Wall -Wextra -lpthread -O2

.PHONY: all clean

all: multi_thread_sort.o



multi_thread_sort.o: 
	$(CC) $(CFLAGS) -o multi_thread_sort.o 1.c



clean:
	rm -f multi_thread_sort.o






valgrind: multi_thread_sort.o
	valgrind --leak-check=full ./multi_thread_sort.o