# -----------------------------------------
#             Server Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

server-objs += logger.o server.o map.o

srv.out: $(server-objs)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(server-objs) srv.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
