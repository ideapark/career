#include <stdio.h>

/*
 * read score range from 0 to 100
 * store to an array
 * return: elements number
 */
int getScores(short scores[], int len)
{
  int i = 0;
  puts("Please enter scores between 0 and 100.\n"
       "Press <Q> and <Return> to quit.\n");
  while (i < len) {
    printf("Score No. %2d: ", i+1);
    if (scanf("%hd", &scores[i]) != 1)
      break;
    if (scores[i] < 0 || scores[i] > 100) {
      printf("%d: Value out of range.\n", scores[i]);
      continue;
    }
    ++i;
  }
  return i;
}

int main(void)
{
#define ARR_LENGTH 10
  short scores[ARR_LENGTH];
  getScores(scores, ARR_LENGTH);
  for (int i = 0; i < ARR_LENGTH; i++)
    printf("%d ", scores[i]);
  return 0;
}
