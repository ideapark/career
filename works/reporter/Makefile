# --------------------------------------------------------------
# reporter.exe  - aps performance tool sample data parsing tool
# callgraph.exe - aps performance tool callgraph tool
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
#
# --------------------------------------------------------------

ccflags := -Wall -O2 -fno-common -DHAVE_CONFIG_H -DDEBUG=0
include := -I. -I.. -I../libutil -I../libopt++ -I../libutil++ -I../libop -I../libpp

cc := clang
CC := clang++

export ccflags include
export cc CC

extralib := -lbfd -lsqlite3 -liberty -lpopt -lstdc++ -ldl -lz -lpthread

all: objects
	$(CC) $(shell find . -type f -name '*.o' | grep -v callgraph.exe) $(extralib) -o target/reporter.exe
	$(CC) $(shell find . -type f -name '*.o' | grep -v reporter.exe) $(extralib) -o target/callgraph.exe

release: all
	strip target/reporter.exe
	strip target/callgraph.exe

objects: copyright
	$(MAKE) -C ./libpp
	$(MAKE) -C ./libutil
	$(MAKE) -C ./libopt++
	$(MAKE) -C ./libutil++
	$(MAKE) -C ./reporter.exe
	$(MAKE) -C ./callgraph.exe

copyright:
	@echo "@-------------------------------------------------------------------@"
	@echo "@                    ADVANCED PERFORMANCE SOLUTION                  @"
	@echo "@                                                                   @"
	@echo "@ Copyright (C) Zhou Peng <lockrecv@qq.com>                         @"
	@echo "@                                                                   @"
	@echo "@ reporter.exe  - data parsing tool                                 @"
	@echo "@ callgraph.exe - callgraph tool                                    @"
	@echo "@                                                                   @"
	@echo "@ PLEASE REFER TO [Documentation/*.txt] FOR HELP.                   @"
	@echo "@-------------------------------------------------------------------@"
