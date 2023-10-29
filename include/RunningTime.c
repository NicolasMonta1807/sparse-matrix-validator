#include "RunningTime.h"

void startTimer(struct times *times)
{

  times->start = clock();
}

void endTimer(struct times *times)
{
  times->end = clock();
  double duration = ((double)times->end - times->start) / CLOCKS_PER_SEC;

  printf("Time elapsed: %f seconds\n", duration);
}
