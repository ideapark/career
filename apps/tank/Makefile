# -----------------------------------------
#             Tank War Makefile
#
# Copyright (c) Zhou Peng <p@ctriple.cn>
# -----------------------------------------

export AR = ar
export CC = gcc
export ARFLAG = rcs
export CFLAGS = -Wall -g -I$(shell pwd)/libutil
export LIBS = -L$(shell pwd)/libutil/ -lutil -lm
export SHELL = /bin/sh

all: compile

compile: copyright
	$(MAKE) -C libutil clean libutil.a
	$(MAKE) -C server clean srv.out
	$(MAKE) -C player clean ply.out

test: compile
	$(SHELL) -c 'cd server && ./srv.out --port=8080 --stdout &'
	$(SHELL) -c 'sleep 3'
	$(SHELL) -c 'cd player && ./ply.out --ip="localhost" --port=8080 --stdout &'
	$(SHELL) -c 'cd player && ./ply.out --ip="localhost" --port=8080 --stdout &'

copyright:
	@echo "### ----------------------------------------- ###"
	@echo "###                 Tank War                  ###"
	@echo "### Copyright (c) Zhou Peng <p@ctriple.cn> ###"
	@echo "### ----------------------------------------- ###"
