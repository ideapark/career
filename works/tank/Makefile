# -----------------------------------------
#                Tank War
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

cc = gcc
cflag = -Wall

export cc cflag

all: server client

server:
	$(MAKE) -C server

client:
	$(MAKE) -C client

%.o: %.c
