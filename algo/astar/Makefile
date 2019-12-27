all: astar.out

CC = gcc
CFLAGS = -Wall -g

astar.out: astar.o main.o
	$(CC) $(CFLAGS) -o $@ $^

astar.o: astar.c
main.o: main.c

clean:
	rm -f *.o astar.out
