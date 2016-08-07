# -----------------------------------------
#             Tank War Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

CC = gcc
CFLAGS = -Wall -g

export CC CFLAGS

all: copyright
	$(MAKE) -C thirdparty/cJSON clean all
	$(MAKE) -C server clean srv.out
	$(MAKE) -C client clean cli.out

copyright:
	@echo "### ----------------------------------------- ###"
	@echo "###                 Tank War                  ###"
	@echo "### Copyright (c) Zhou Peng <lockrecv@qq.com> ###"
	@echo "### ----------------------------------------- ###"
