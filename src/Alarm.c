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
  Alarm_Start(alarm);
}

bool Alarm_IsExpired(Alarm_t * alarm)
{
  Clock_Val_t c = Clock_Get();
  Clock_Val_t diff = c - alarm->started_at;
  bool expired = diff > alarm->duration;

  return expired;
}
