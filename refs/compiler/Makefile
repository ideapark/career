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

all: clean tcc tm

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

tcc: $(tcc-objs)
	$(CC) $(CFLAG) $(tcc-objs) -o $@

tm: $(tm-objs)
	$(CC) $(CFLAG) $(tm-objs) -o $@

clean:
	@rm -f $(tcc-objs) $(tm-objs) tcc tm
