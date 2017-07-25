# ----------------------------------------------
# Copyright (C) Zhou Peng <p@ctriple.cn>
# ----------------------------------------------

objs += op_deviceio.o
objs += op_lockfile.o
objs += op_file.o
objs += op_fileio.o
objs += op_get_time.o
objs += op_libiberty.o
objs += op_popt.o
objs += op_string.o
objs += op_cpufreq.o
objs += op_version.o
objs += op_growable_buffer.o

all: $(objs)

op_deviceio.o: op_deviceio.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_lockfile.o: op_lockfile.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_file.o: op_file.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_fileio.o: op_fileio.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_get_time.o: op_get_time.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_libiberty.o: op_libiberty.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_popt.o: op_popt.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_string.o: op_string.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_cpufreq.o: op_cpufreq.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_version.o: op_version.c
	$(cc) $(ccflags) $(include) -c $< -o $@

op_growable_buffer.o: op_growable_buffer.c
	$(cc) $(ccflags) $(include) -c $< -o $@
