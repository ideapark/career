# -----------------------------------------
#             Tank War Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

export AR = ar
export CC = gcc
export ARFLAG = rcs
export CFLAGS = -Wall -g -I$(shell pwd)/lib
export LIBS = -L$(shell pwd)/lib/ -lopen -lm

all: copyright
	$(MAKE) -C lib clean libopen.a
	$(MAKE) -C srv clean srv.out
	$(MAKE) -C cli clean cli.out

copyright:
	@echo "### ----------------------------------------- ###"
	@echo "###                 Tank War                  ###"
	@echo "### Copyright (c) Zhou Peng <lockrecv@qq.com> ###"
	@echo "### ----------------------------------------- ###"
