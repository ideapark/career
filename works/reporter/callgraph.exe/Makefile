# ----------------------------------------------
# Copyright (c) Zhou Peng <p@ctriple.cn>
# ----------------------------------------------

objs += callgraph_main.o
objs += callgraph_options.o
objs += callgraph_painter.o
objs += callgraph_sqlite.o

all: $(objs)

callgraph_main.o: callgraph_main.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

callgraph_options.o: callgraph_options.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

callgraph_painter.o: callgraph_painter.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

callgraph_sqlite.o: callgraph_sqlite.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@
