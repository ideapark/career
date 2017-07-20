# -----------------------------------------
#             Player Makefile
#
# Copyright (c) Zhou Peng <p@ctriple.cn>
# -----------------------------------------

ply-objs += player.o link.o

ply.out: $(ply-objs)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -rf $(ply-objs) ply.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
