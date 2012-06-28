#include "Clock.h"
#include <avr/interrupt.h>

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
  Clock_Val_t val;

  cli(); // Disable interrupts.
  val = clock;
  sei(); // Enable interrupts.

  return val;
}

void Clock_Set(Clock_Val_t time_to_set)
{
  cli(); // Disable interrupts.
  clock = time_to_set;
  sei(); // Enable interrupts.
}
