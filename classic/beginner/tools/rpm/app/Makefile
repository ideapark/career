all: myapp

# which compiler
CC=gcc

# archive
AR=ar

# archive option
ARFLAGS=rv

# where are include files kept
INCLUDE=.

# options for development
CFLAGS=-g -Wall -ansi

# options for release
# CFLAGS=-O -Wall -ansi

# local libraries
MYLIB=mylib.a

myapp: main.o $(MYLIB)
	$(CC) -o $@ $?

$(MYLIB): 2.o 3.o
	$(AR) $(ARFLAGS) $@ $?

main.o: main.c a.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $< -o $@

2.o: 2.c a.h b.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $< -o $@

3.o: 3.c b.h c.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	-rm *.o
	-rm $(MYLIB)
	-rm myapp
	-rm -rf myapp-1.0
	-rm myapp-1.0.tar.gz

dist: myapp-1.0.tar.gz

myapp-1.0.tar.gz: myapp myapp.1
	-rm -rf myapp-1.0
	mkdir myapp-1.0
	cp *.c *.h *.1 Makefile myapp-1.0
	tar zcvf $@ myapp-1.0
