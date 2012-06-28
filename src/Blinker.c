#include "Blinker.h"
#include "Alarm.h"

#include <avr/io.h>

void Blinker_Init(Blinker_t * blinker)
{
  Alarm_t * alarm = &(blinker->alarm);

  blinker->interval = DEFAULT_BLINKER_INTERVAL;

  Blinker_LED_Init(&blinker->led, &PORTB, PORTB5);
  Alarm_Init(alarm, blinker->interval);
  Alarm_Start(alarm);

}

void Blinker_Service(Blinker_t * blinker)
{
  Alarm_t * alarm = &blinker->alarm;

  if (Alarm_IsExpired(alarm))
  {
    Blinker_LED_Toggle(&blinker->led);
    if (blinker->reinit_alarm)
    {
      Alarm_Init(alarm, blinker->interval);
      blinker->reinit_alarm = false;
    }
    else
    {
      Alarm_Reset(alarm);
    }
  }
}

void Blinker_UpdateInterval(Blinker_t * blinker, Clock_Val_t interval)
{
  blinker->interval = interval;
  blinker->reinit_alarm = true;
}
