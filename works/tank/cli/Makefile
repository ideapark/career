# -----------------------------------------
#             Client Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

cli-objs += client.o link.o

cli.out: $(cli-objs)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -rf $(cli-objs) cli.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
