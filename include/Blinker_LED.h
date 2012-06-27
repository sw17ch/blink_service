#ifndef Blinker_LED_H
#define Blinker_LED_H

#include <stdint.h>


typedef volatile uint8_t * Port_t;

typedef struct {
  Port_t port;
  uint8_t pin;
} Blinker_LED_t;

void Blinker_LED_Toggle(Blinker_LED_t * led);

#endif // Blinker_LED_H
