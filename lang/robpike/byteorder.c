#include <stdio.h>

/* byteorder: display bytes of a long */
int main(void)
{
  unsigned long x;
  unsigned char *p;
  int i;

  /* 11 22 33 44 => big-endian */
  /* 44 33 22 11 => little-endian */
  /* x = 0x1122334455667788UL; for 64-bit long */
  x = 0x11223344UL;
  p = (unsigned char *) &x;
  for (i = 0; i < sizeof(long); i++)
    printf("%x ", *p++);
  printf("\n");

  return 0;
}
