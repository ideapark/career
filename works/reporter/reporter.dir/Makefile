# ----------------------------------------------
# Copyright (c) Zhou Peng <p@ctriple.cn>
# ----------------------------------------------

objs += reporter_main.o
objs += reporter_options.o
objs += reporter_fileloader.o
objs += reporter_samplefile.o
objs += reporter_avltree.o
objs += reporter_bfdsymbol.o
objs += reporter_models.o
objs += reporter_sqlite.o
objs += reporter_transfer.o
objs += reporter_consts.o

all: $(objs)

reporter_main.o: reporter_main.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_options.o: reporter_options.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_fileloader.o: reporter_fileloader.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_samplefile.o: reporter_samplefile.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_avltree.o: reporter_avltree.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_bfdsymbol.o: reporter_bfdsymbol.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_models.o: reporter_models.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_sqlite.o: reporter_sqlite.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_transfer.o: reporter_transfer.cc
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_consts.o: reporter_consts.cc
	$(CC) $(ccflags) $(include) -c $< -o $@
