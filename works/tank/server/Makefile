# -----------------------------------------
#             Server Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

server-objs += logger.o server.o map.o link.o

srv.out: $(server-objs)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -rf $(server-objs) srv.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
