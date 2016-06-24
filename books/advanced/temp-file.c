/*
 * Create a Temporary File
 */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Returns the file descriptor for a newly created temporary file.
 * The temporary file will be readable and writable by the effective
 * user ID of the current process but will not be readable or writable
 * by anybody else.
 *
 * Returns -1 if the temporary file could not be created.
 */
int secure_temp_file()
{
  /*
   * This file descriptor points to /dev/random and allows us to get
   * a good source of random bits.
   */
  static int random_fd = -1;
  unsigned int random;
  char filename[128];
  int fd;
  struct stat stat_buf;

  if (random_fd == -1) {
    random_fd = open("/dev/random", O_RDONLY);
    if (random_fd == -1)
      return -1;
  }

  if (read(random_fd, &random, sizeof(random)) != sizeof(random))
    return -1;

  sprintf(filename, "/tmp/%u", random);
  fd = open(filename, O_RDWR|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR);
  if (fd == -1)
    return -1;

  if (lstat(filename, &stat_buf) == -1)
    return -1;

  if (!S_ISREG(stat_buf.st_mode))
    return -1;

  if (stat_buf.st_uid != geteuid() || stat_buf.st_gid != getegid())
    return -1;

  if ((stat_buf.st_mode & !(S_IRUSR|S_IWUSR)) != 0)
    return -1;

  return fd;
}
