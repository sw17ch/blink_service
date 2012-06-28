#include "Blinker.h"
#include "Alarm.h"

void Blinker_Service(Blinker_t * blinker)
{
  if (Alarm_IsExpired(&blinker->alarm))
  {
    Blinker_LED_Toggle(&blinker->led);
  }
}
