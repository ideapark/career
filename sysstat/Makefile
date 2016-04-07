# --------------------------------------------------------------
# sysstat   - system performance sample tool
# sysparser - system performance data parsing tool
#
# Copyright (C) Zhou Peng <lockrecv@qq.com>
# --------------------------------------------------------------

cflag = -O2 -Wall -Werror
cinc = -I.

SYSSTAT_OBJS += main.o irq.o sys.o task.o vm.o misc_helper.o mapped_helper.o
PARSER_OBJS += main_parser.o irq_parser.o sys_parser.o task_parser.o vm_parser.o sqlite_helper.o
EXTRA_LIBS += -lpthread -ldl -lsqlite3

all: sysstat sysparser

clean:
	rm -f $(SYSSTAT_OBJS) sysstat
	rm -f $(PARSER_OBJS) sysparser

sysstat: clean $(SYSSTAT_OBJS)
	$(CC) $(SYSSTAT_OBJS) -o sysstat

sysparser: clean $(PARSER_OBJS)
	$(CC) $(PARSER_OBJS) $(EXTRA_LIBS) -o sysparser


####################

main.o: core/main.c
	$(CC) $(cflag) $(cinc) -c core/main.c

irq.o: irq/irq.c
	$(CC) $(cflag) $(cinc) -c irq/irq.c

sys.o: sys/sys.c
	$(CC) $(cflag) $(cinc) -c sys/sys.c

vm.o: vm/vm.c
	$(CC) $(cflag) $(cinc) -c vm/vm.c

task.o: task/task.c
	$(CC) $(cflag) $(cinc) -c task/task.c

mapped_helper.o: util/mapped_helper.c
	$(CC) $(cflag) $(cinc) -c util/mapped_helper.c

misc_helper.o: util/misc_helper.c
	$(CC) $(cflag) $(cinc) -c util/misc_helper.c


main_parser.o: core/main_parser.c
	$(CC) $(cflag) $(cinc) -c core/main_parser.c

irq_parser.o: irq/irq_parser.c
	$(CC) $(cflag) $(cinc) -c irq/irq_parser.c

sys_parser.o: sys/sys_parser.c
	$(CC) $(cflag) $(cinc) -c sys/sys_parser.c

vm_parser.o: vm/vm_parser.c
	$(CC) $(cflag) $(cinc) -c vm/vm_parser.c

task_parser.o: task/task_parser.c
	$(CC) $(cflag) $(cinc) -c task/task_parser.c

sqlite_helper.o: util/sqlite_helper.c
	$(CC) $(cflag) $(cinc) -c util/sqlite_helper.c

####################
