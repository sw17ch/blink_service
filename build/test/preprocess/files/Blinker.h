#include "Blinker_LED.h"
#include "Alarm.h"








typedef struct {

  Alarm_t alarm;

  Blinker_LED_t led;

} Blinker_t;



void Blinker_Service(Blinker_t * blinker);
