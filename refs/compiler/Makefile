# ------------------------------------------
#  Copyright (c) Zhou Peng <lockrecv@qq.com>
# ------------------------------------------

CC := gcc
CFLAG := -Wall

tc-objs += util.o \
	symtab.o \
	cgen.o \
	code.o \
	parse.o \
	scan.o \
	analyze.o \
	main.o

tm-objs += tm.o

all: clean tc tm

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

tc: $(tc-objs)
	$(CC) $(CFLAG) $(tc-objs) -o $@

tm: $(tm-objs)
	$(CC) $(CFLAG) $(tm-objs) -o $@

clean:
	@rm -f $(tc-objs) $(tm-objs) tc tm
