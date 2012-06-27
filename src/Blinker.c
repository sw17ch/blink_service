#include "Blinker.h"
#include "Alarm.h"

void Blinker_Service(Blinker_t * blinker)
{
  Alarm_IsExpired(&blinker->alarm);
  Blinker_LED_Toggle(&blinker->led);
}
