# -----------------------------------------
#             Library Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

open-objs += logger.o cJSON.o

libopen.a: $(open-objs)
	$(AR) $(ARFLAG) $@ $^

clean:
	@rm -rf $(open-objs) libopen.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
