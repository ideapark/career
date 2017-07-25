# --------------------------------------------------------------
# reporter.exe  - aps performance tool sample data parsing tool
# callgraph.exe - aps performance tool callgraph tool
#
# Copyright (c) Zhou Peng <p@ctriple.cn>
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
	$(CC) $(shell find . -type f -name '*.o' | grep -v callgraph.exe) $(extralib) -o reporter
	$(CC) $(shell find . -type f -name '*.o' | grep -v reporter.exe) $(extralib) -o callgraph

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
	@echo "@                                                                   @"
	@echo "@ Copyright (c) Zhou Peng <p@ctriple.cn>                            @"
	@echo "@                                                                   @"
	@echo "@ reporter.exe  - data parsing tool                                 @"
	@echo "@ callgraph.exe - callgraph tool                                    @"
	@echo "@                                                                   @"
	@echo "@ Please refer to [Documentation/*.txt] for help.                   @"
	@echo "@-------------------------------------------------------------------@"
