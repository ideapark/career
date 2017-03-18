# -----------------------------------------
#             Library Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

util-objs += logger.o cJSON.o

libutil.a: $(util-objs)
	$(AR) $(ARFLAG) $@ $^

clean:
	@rm -rf $(util-objs) libutil.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
