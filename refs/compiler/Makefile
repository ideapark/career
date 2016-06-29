# ------------------------------------------
#  Copyright (c) Zhou Peng <lockrecv@qq.com>
# ------------------------------------------

CC := gcc
CFLAG := -Wall

tcc-objs += util.o \
	    symtab.o \
	    cgen.o \
	    code.o \
	    parse.o \
	    scan.o \
	    analyze.o \
	    main.o

tm-objs += tm.o

.PHONY: all

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

tcc: $(tcc-objs)
	$(CC) $(tcc-objs) -o $@

tm: $(tm-objs)
	$(CC) $(tm-objs) -o $@

all: tcc tm
