/*
• Reading from and writing to a memory-mapped file avoids the extraneous copy
  that occurs when using the read() or write() system calls, where the data
  must be copied to and from a user-space buffer.

• Aside from any potential page faults, reading from and writing to a memory-
  mapped file does not incur any system call or context switch overhead. It is
  as simple as accessing memory.

• When multiple processes map the same object into memory, the data is shared
  among all the processes. Read-only and shared writable mappings are shared
  in their entirety; private writable mappings have their not-yet-COW
  (copy-on-write) pages shared.

• Seeking around the mapping involves trivial pointer manipulations. There is
  no need for the lseek() system call.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  struct stat sb;
  off_t len;
  char *p;
  int fd;

  if (argc < 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    return 1;
  }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    return 1;
  }

  if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "%s is not a file\n", argv[1]);
    return 1;
  }

  p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  if (close(fd) == -1) {
    perror("close");
    return 1;
  }

  for (len = 0; len < sb.st_size; len++) {
    putchar(p[len]);
  }

  if (munmap(p, sb.st_size) == -1) {
    perror("munmap");
    return 1;
  }

  return 0;
}
