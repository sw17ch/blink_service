#include "Alarm.h"

void Alarm_Init(Alarm_t * alarm, Clock_Val_t duration);
void Alarm_Start(Alarm_t * alarm);
void Alarm_Reset(Alarm_t * alarm);

bool Alarm_IsExpired(Alarm_t * alarm)
{
  return true;
}
