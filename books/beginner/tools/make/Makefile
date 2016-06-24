all: myapp

# which compiler
CC=gcc

# archive
AR=ar

# archive option
ARFLAGS=rv

# where to install
INSTDIR=$(HOME)

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

main.o: main.c a.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<

2.o: 2.c a.h b.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<

3.o: 3.c b.h c.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<

$(MYLIB): 2.o 3.o
	$(AR) $(ARFLAGS) $@ $?

clean:
	-rm *.o myapp $(MYLIB)

install: myapp
	@if [ -d $(INSTDIR) ];                              \
    then                                                \
        cp myapp $(INSTDIR) &&                          \
        chmod a+x $(INSTDIR)/myapp &&                   \
        chmod og-w $(INSTDIR)/myapp &&                  \
        echo "Installed in $(INSTDIR)";                 \
    else                                                \
        echo "Sorry, $(INSTDIR) does not exist"; false; \
    fi

uninstall:
	-rm $(INSTDIR)/myapp
