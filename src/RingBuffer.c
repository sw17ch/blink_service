#include "RingBuffer.h"

void RingBuffer_Init(RingBuffer_t * rb, uint8_t * backing, size_t size)
{
  rb->backing      = backing;
  rb->backing_size = size;
  rb->head         = 0;
  rb->tail         = 0;
  rb->len          = 0;
}

bool RingBuffer_Put(RingBuffer_t * rb, uint8_t val)
{
  if (rb->len > 0 && rb->tail == rb->head)
  {
    return false;
  }

  rb->backing[rb->tail] = val;
  rb->len++;
  rb->tail = (rb->tail + 1) % rb->backing_size;

  return true;
}

bool RingBuffer_Get(RingBuffer_t * rb, uint8_t * val)
{
  if (rb->len <= 0)
  {
    return false;
  }

  *val = rb->backing[rb->head];
  rb->head = (rb->head + 1) % rb->backing_size;
  rb->len--;

  return true;
}

void RingBuffer_Reset(RingBuffer_t * rb)
{
  rb->len = 0;
  rb->head = 0;
  rb->tail = 0;
}
