#include "Blinker.h"
#include "Alarm.h"

#include <avr/io.h>

void Blinker_Init(Blinker_t * blinker)
{
  Alarm_t * alarm = &(blinker->alarm);

  Blinker_LED_Init(&blinker->led, &PORTB, PORTB5);
  Alarm_Init(alarm, 500);
  Alarm_Start(alarm);
}

void Blinker_Service(Blinker_t * blinker)
{
  Alarm_t * alarm = &blinker->alarm;

  if (Alarm_IsExpired(alarm))
  {
    Blinker_LED_Toggle(&blinker->led);
    Alarm_Reset(alarm);
  }
}
