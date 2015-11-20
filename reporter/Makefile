# --------------------------------------------------------------
# reporter.exe  - aps performance tool sample data parsing tool
# callgraph.exe - aps performance tool callgraph tool
#
# Copyright (C) Zhou Peng <lockrecv@gmail.com>
#
# --------------------------------------------------------------

ccflags := -Wall -O2 -fno-common -DHAVE_CONFIG_H
include := -I. -I.. -I../libutil -I../libopt++ -I../libutil++ -I../libop -I../libpp
cc := gcc
CC := g++

export ccflags include cc CC

extralib := -lbfd -lsqlite3 -liberty -lpopt -lstdc++ -ldl -lz -lpthread

all: objects
	$(CC) $(shell find . -type f -name '*.o' | grep -v callgraph.exe) $(extralib) -o reporter
	$(CC) $(shell find . -type f -name '*.o' | grep -v reporter.exe) $(extralib) -o callgraph

release: all
	strip target/reporter.exe
	strip target/callgraph.exe

objects: help
	$(MAKE) -C ./libpp
	$(MAKE) -C ./libutil
	$(MAKE) -C ./libopt++
	$(MAKE) -C ./libutil++
	$(MAKE) -C ./reporter.exe
	$(MAKE) -C ./callgraph.exe

help:
	@echo "---------------------------------------------------"
	@echo "           ADVANCED PERFORMANCE SOLUTION           "
	@echo "                                                   "
	@echo " Copyright (C) Zhou Peng <lockrecv@gmail.com>      "
	@echo "                                                   "
	@echo " reporter.exe  - data parsing tool                 "
	@echo " callgraph.exe - callgraph tool                    "
	@echo "                                                   "
	@echo " PLEASE REFER TO [Documentation/*.txt] FOR HELP.   "
	@echo "---------------------------------------------------"
