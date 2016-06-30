# ------------------------------------------
#  Copyright (c) Zhou Peng <lockrecv@qq.com>
# ------------------------------------------

CC := gcc
CFLAG := -Wall

cc-objs += util.o \
	symtab.o \
	cgen.o \
	code.o \
	parse.o \
	scan.o \
	analyze.o \
	main.o

tm-objs += tm.o

all: clean cc tm

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

cc: $(cc-objs)
	$(CC) $(CFLAG) $(cc-objs) -o $@

tm: $(tm-objs)
	$(CC) $(CFLAG) $(tm-objs) -o $@

clean:
	@rm -f $(cc-objs) $(tm-objs) cc tm
