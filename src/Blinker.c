#include "Blinker.h"
#include "Alarm.h"

#include <avr/io.h>

void Blinker_Init(Blinker_t * blinker)
{
  Blinker_LED_Init(&blinker->led, &PORTB, PORTB5);
}

void Blinker_Service(Blinker_t * blinker)
{
  if (Alarm_IsExpired(&blinker->alarm))
  {
    Blinker_LED_Toggle(&blinker->led);
  }
}
