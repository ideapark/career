# ---------------------------------------------
#      BREADTH FIRST SEARCH AlGORITHM
#
# Copyright (C) Zhou Peng <lockrecv@gmail.com>
#
# ---------------------------------------------

CC = g++
cflag = -Wall

objs += bfs_main.o
objs += bfs_impl.o

bfs.out: $(objs)
	$(CC) $(objs) -o $@

bfs_main.o: bfs_main.cc
	$(CC) $(cflag) -c $< -o $@

bfs_impl.o: bfs_impl.cc
	$(CC) $(cflag) -c $< -o $@

