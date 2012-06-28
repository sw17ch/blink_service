#include "Alarm.h"
#include "Clock.h"

#include <stdbool.h>

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
  return (Clock_Get() - alarm->started_at) >= alarm->duration;
}
