# ----------------------------------------------
# Copyright (C) Zhou Peng <p@ctriple.cn>
# ----------------------------------------------

objs += bfd_support.o
objs += child_reader.o
objs += cverb.o
objs += file_manip.o
objs += glob_filter.o
objs += op_bfd.o
objs += op_exception.o
objs += path_filter.o
objs += stream_util.o
objs += string_filter.o
objs += string_manip.o

all: $(objs)

bfd_support.o: bfd_support.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

child_reader.o: child_reader.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

cverb.o: cverb.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

file_manip.o: file_manip.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

glob_filter.o: glob_filter.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

op_bfd.o: op_bfd.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

op_exception.o: op_exception.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

path_filter.o: path_filter.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

stream_util.o: stream_util.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

string_filter.o: string_filter.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

string_manip.o: string_manip.cc
	$(CC) $(ccflags) $(include) -c $< -o $@
