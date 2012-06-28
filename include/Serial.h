#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

typedef struct {
  uint16_t port;
} Serial_t;

void Serial_Init(Serial_t * serial, uint16_t port);
void Serial_Service(Serial_t * serial);

#endif /* SERIAL_H */
