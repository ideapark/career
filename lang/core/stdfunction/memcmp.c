#include <string.h>
#include <stdio.h>

int main(void)
{
  long setone[5] = { 1, 3, 5, 7, 9 };
  long settwo[5] = { 0, 2, 4, 6, 8 };

  for (int i = 0; i < 5; i++)
    settwo[i] += 1;

  if (memcmp(&setone[0], &settwo[0], sizeof(settwo)) == 0)
    printf("The two arrays are idential, byte for byte.\n");

  return 0;
}
