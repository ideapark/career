#include <unistd.h>
#include <stdio.h>

#define LOOP_STATS(stat, cnt)      \
  for (long i = 0; i < cnt; i++) { \
    stat;                          \
  }

int main(int argc, char *argv[])
{
  const static long loop_cnt = 100;

  printf("stdout is buffered:");
  fflush(stdout);
  LOOP_STATS({
      printf(".");
      sleep(1);
      }, loop_cnt);

  fprintf(stderr, "\n");

  fprintf(stderr, "stderr is not buffered:");
  LOOP_STATS({
      fprintf(stderr, ".");
      sleep(1);
      }, loop_cnt);

  return 0;
}
