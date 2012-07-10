#include "RingBuffer.h"

void RingBuffer_Init(RingBuffer_t * rb, uint8_t * backing, size_t size)
{
  rb->backing = backing;
  rb->head = 0;
  rb->tail = 0;
  rb->len = 0;
}

bool RingBuffer_Put(RingBuffer_t * rb, uint8_t val)
{
  rb->backing[rb->tail] = val;
  rb->tail++;

  return true;
}
