#ifndef Echo_H
#define Echo_H

#include "Serial.h"

#include <stdint.h>

#define ECHO_BUFFER_SIZE (16)

typedef struct {
  uint8_t buffer[ECHO_BUFFER_SIZE];
} Echo_t;

void Echo_Init(Echo_t * echo);
void Echo_Service(Echo_t * echo, Serial_t * serial);

#endif // Echo_H
