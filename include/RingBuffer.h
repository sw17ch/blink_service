#ifndef RingBuffer_H
#define RingBuffer_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  uint8_t * backing; // The buffer backing the ring.
  size_t size;       // The size of the backing buffer.
  size_t head;       // The head of the ring buffer.
  size_t tail;       // The last element in the ring buffer.
  size_t len;        // The number of elements in the ring buffer.
} RingBuffer_t;

void RingBuffer_Init(RingBuffer_t * rb, uint8_t * backing, size_t size);
bool RingBuffer_Put(RingBuffer_t * rb, uint8_t val);

#endif // RingBuffer_H
