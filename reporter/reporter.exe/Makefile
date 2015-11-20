# ----------------------------------------------
# Copyright (C) Zhou Peng <lockrecv@gmail.com>
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

reporter_main.o: reporter_main.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_options.o: reporter_options.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_fileloader.o: reporter_fileloader.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_samplefile.o: reporter_samplefile.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_avltree.o: reporter_avltree.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_bfdsymbol.o: reporter_bfdsymbol.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_models.o: reporter_models.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_sqlite.o: reporter_sqlite.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_transfer.o: reporter_transfer.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@

reporter_consts.o: reporter_consts.cpp
	$(CC) $(ccflags) $(include) -c $< -o $@
