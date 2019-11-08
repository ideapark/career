# Kiss Makefile

CC = cc
AR = ar
RM = rm -f

CFLAGS = -c -O2 -Wall
ARFLAGS = -r

LIBKISS = libkiss.a

SRCS += src/grep.c
SRCS += src/cut.c
SRCS += src/diff.c
SRCS += src/uniq.c
SRCS += src/sort.c
SRCS += src/sed.c

TESTS += test/test-grep.c
TESTS += test/test-cut.c
TESTS += test/test-diff.c
TESTS += test/test-uniq.c
TESTS += test/test-sort.c
TESTS += test/test-sed.c

SRC_OBJS += grep.o
SRC_OBJS += cut.o
SRC_OBJS += diff.o
SRC_OBJS += uniq.o
SRC_OBJS += sort.o
SRC_OBJS += sed.o

TEST_OBJS += test-grep.o
TEST_OBJS += test-cut.o
TEST_OBJS += test-diff.o
TEST_OBJS += test-uniq.o
TEST_OBJS += test-sort.o
TEST_OBJS += test-sed.o


help:
	@echo 'Keep It Simple Stupid'
	@echo ''
	@echo '  archive      Archive library'
	@echo '  test         Run all unit tests'
	@echo '  clean        Clean environment'
	@echo ''

.compile:
	$(CC) $(CFLAGS) $(SRCS)

archive: .compile
	$(AR) $(ARFLAGS) $(LIBKISS) $(SRC_OBJS)

test: .compile
	$(CC) $(CFLAGS) $(TESTS)

clean:
	$(RM) $(SRC_OBJS)
	$(RM) $(TEST_OBJS)
	$(RM) $(LIBKISS)

.PHONY: help
