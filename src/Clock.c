#include "Clock.h"

static Clock_Val_t clock = 0;

void Clock_Tick(void)
{
  clock++;
}

void Clock_Reset(void)
{
  clock = 0;
}

Clock_Val_t Clock_Get(void)
{
  return clock;
}

void Clock_Set(Clock_Val_t time_to_set)
{
  clock = time_to_set;
}
