# ---------------------------------------------
#      BREADTH FIRST SEARCH AlGORITHM
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
#
# ---------------------------------------------

CC = g++
cflag = -Wall -DBFS_DEBUG

objs += bfs_main.o
objs += bfs_impl.o

bfs.out: $(objs)
	$(CC) $(objs) -o $@

bfs_main.o: bfs_main.cc
	$(CC) $(cflag) -c $< -o $@

bfs_impl.o: bfs_impl.cc
	$(CC) $(cflag) -c $< -o $@

