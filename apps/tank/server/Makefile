# -----------------------------------------
#             Server Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

srv-objs += server.o map.o link.o

srv.out: $(srv-objs)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -rf $(srv-objs) srv.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
