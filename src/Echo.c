#include "Echo.h"

#include <string.h>

void Echo_Init(Echo_t * echo)
{
  memset(echo->buffer, 0, sizeof(echo->buffer));
}

void Echo_Service(Echo_t * echo, Serial_t * serial)
{
  size_t gotten = Serial_Get(serial, echo->buffer, sizeof(echo->buffer));
  Serial_Put(serial, echo->buffer, gotten);
}
