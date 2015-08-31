# ---------------------------------------------
#      BREADTH FIRST SEARCH AlGORITHM
#
# Copyright (C) Zhou Peng <lockrecv@gmail.com>
#
# ---------------------------------------------

cflag += -Wall
objs += bfs_main.o
objs += bfs_impl.o

bfs.out: $(objs)
	g++ $(objs) -o $@

bfs_main.o: bfs_main.cc
	g++ $(cflag) -c $< -o $@

bfs_impl.o: bfs_impl.cc
	g++ $(cflag) -c $< -o $@

