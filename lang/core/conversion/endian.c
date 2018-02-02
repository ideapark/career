#include <stdio.h>

struct Data {
  short id;
  double val;
};

int main(void)
{
  int i;
  struct Data myData = { 0x123, 77.7 };
  unsigned char *cp = (unsigned char *)&myData;
  printf("%p: ", cp);
  for (i = 0; i < sizeof(myData); ++i)
    printf("%02X ", *(cp+i));
  putchar('\n');
  return 0;
}
