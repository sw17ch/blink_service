#ifndef Blinker_H
#define Blinker_H

#include "Alarm.h"
#include "Blinker_LED.h"
#include "Clock.h"

#define DEFAULT_BLINKER_INTERVAL (1000)

typedef struct {
  Alarm_t alarm;
  Blinker_LED_t led;

  Clock_Val_t interval; 
  bool reinit_alarm;
} Blinker_t;

void Blinker_Init(Blinker_t * blinker);
void Blinker_Service(Blinker_t * blinker);
void Blinker_UpdateInterval(Blinker_t * blinker, Clock_Val_t interval);

#endif // Blinker_H
