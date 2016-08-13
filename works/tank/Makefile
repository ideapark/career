# -----------------------------------------
#             Tank War Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

export AR = ar
export CC = gcc
export ARFLAG = rcs
export CFLAGS = -Wall -g -I$(shell pwd)/libutil
export LIBS = -L$(shell pwd)/libutil/ -lutil -lm

all: copyright
	$(MAKE) -C libutil clean libutil.a
	$(MAKE) -C server clean srv.out
	$(MAKE) -C player clean ply.out

copyright:
	@echo "### ----------------------------------------- ###"
	@echo "###                 Tank War                  ###"
	@echo "### Copyright (c) Zhou Peng <lockrecv@qq.com> ###"
	@echo "### ----------------------------------------- ###"
