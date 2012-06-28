#include "Serial.h"

void Serial_Init(Serial_t * serial, uint16_t port)
{
  serial->port = port;
}

void Serial_Service(Serial_t * serial)
{
}
