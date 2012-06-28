#include "Blinker_LED.h"

void Blinker_LED_Init(Blinker_LED_t * led, Port_t port, uint8_t pin)
{
  led->port = port;
  led->pin = pin;
}

void Blinker_LED_Toggle(Blinker_LED_t * led)
{
  *(led->port) ^= 1 << led->pin;
}
