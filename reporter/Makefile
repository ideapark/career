# --------------------------------------------------------------
# reporter.exe  - aps performance tool sample data parsing tool
# callgraph.exe - aps performance tool callgraph tool
#
# Copyright (C) Zhou Peng <lockrecv@gmail.com>
#
# --------------------------------------------------------------

ccflags := -Wall -g -O2 -fno-common -DHAVE_CONFIG_H
include := -I. -I.. -I../libutil -I../libopt++ -I../libutil++ -I../libop -I../libpp

export ccflags include

extralib := -lbfd -lsqlite3 -liberty -lpopt -lstdc++ -ldl -lz -lpthread -lintl

all: objects
        g++ $(shell find . -type f -name '*.o' | grep -v callgraph.exe) $(extralib) -o target/reporter.exe
        g++ $(shell find . -type f -name '*.o' | grep -v reporter.exe) $(extralib) -o target/callgraph.exe

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
        @echo " Copyright (C) Huawei Technologies Co,. Ltd.       "
        @echo " Copyright (C) Zhou Peng <lockrecv@gmail.com>      "
        @echo "                                                   "
        @echo " reporter.exe  - data parsing tool                 "
        @echo " callgraph.exe - callgraph tool                    "
        @echo "                                                   "
        @echo " PLEASE REFER TO [Documentation/*.txt] FOR HELP.   "
        @echo "---------------------------------------------------"
