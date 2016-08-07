# -----------------------------------------
#             Client Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

client-objs += client.o

cli.out: $(client-objs)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(client-objs) cli.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
