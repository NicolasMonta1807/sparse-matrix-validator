#ifndef __RUNNINGTIME_H__
#define __RUNNINGTIME_H__

#include <time.h>
#include <stdio.h>

struct times
{
  clock_t start;
  clock_t end;
};

void startTimer(struct times *times);
void endTimer(struct times *times);

#endif // __RUNNINGTIME_H__
