#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
#define MSGLEN_MAX 256
  FILE *fp;
  char msgbuf[MSGLEN_MAX] = "";

  if ((fp = fopen("nonexistentfile", "r")) == NULL) {
    snprintf(msgbuf, MSGLEN_MAX, "%s, function %s, file %s, line %d",
             argv[0], __func__, __FILE__, __LINE__);
    perror(msgbuf);
    return errno;
  }
  return 0;
}
