#ifndef Blinker_H
#define Blinker_H

#include "Alarm.h"
#include "Blinker_LED.h"

typedef struct {
  Alarm_t alarm;
  Blinker_LED_t led;
} Blinker_t;

void Blinker_Init(Blinker_t * blinker);
void Blinker_Service(Blinker_t * blinker);

#endif // Blinker_H
