#include "Alarm.h"
#include "Clock.h"
#include "hserial.h"

#include <stdbool.h>
#include <stdio.h>

/* void print_alarm(char * p, Alarm_t * alarm, Clock_Val_t c) */
/* { */
/*   char buffer[128]; */
/*  */
/*   snprintf(buffer, sizeof(buffer), "%s diff:%lu, dur:%lu, clk:%lu, start:%lu\n", */
/*       p, */
/*       c - alarm->started_at, */
/*       alarm->duration, */
/*       c, */
/*       alarm->started_at); */
/*   hs_writeStr(0, buffer); */
/* } */

void Alarm_Init(Alarm_t * alarm, Clock_Val_t duration)
{
  alarm->duration = duration;
  alarm->started = false;
}

void Alarm_Start(Alarm_t * alarm)
{
  alarm->started_at = Clock_Get();
  alarm->started = true;
}

void Alarm_Reset(Alarm_t * alarm)
{
  if (!alarm->started)
  {
    Alarm_Start(alarm);
  }
  else
  {
    alarm->started_at += alarm->duration;
  }
}

bool Alarm_IsExpired(Alarm_t * alarm)
{
  Clock_Val_t c = Clock_Get();
  Clock_Val_t diff = c - alarm->started_at;
  bool expired = diff > alarm->duration;

  return expired;
}
