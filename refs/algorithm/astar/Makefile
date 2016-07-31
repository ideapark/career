all: test.out

CC = gcc
CFLAGS = -Wall -g

test.out: astar.o test.o
	$(CC) $(CFLAGS) -o $@ $^

astar.o: astar.c
test.o: test.c

clean:
	rm -f *.o test.out
