# -----------------------------------------
#             Player Makefile
#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
# -----------------------------------------

ply-objs += player.o link.o

ply.out: $(ply-objs)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -rf $(ply-objs) ply.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
