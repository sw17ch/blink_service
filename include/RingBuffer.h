#ifndef RingBuffer_H
#define RingBuffer_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  uint8_t * backing;   // The buffer backing the ring.
  size_t backing_size; // The size of the backing buffer.
  size_t head;         // The head of the ring buffer.
  size_t tail;         // The last element in the ring buffer.
  size_t len;          // The number of elements in the ring buffer.
} RingBuffer_t;

/**
 * RingBuffer_Init
 *  Initialize a ring buffer.
 *
 * Param rb
 *  A pointer to the ring buffer we wish to initialize.
 *
 * Param backing
 *  A pointer to the buffer to use as the ring buffer's storage space.
 *
 * Param size
 *  The size of the memory pointed to by `backing`
 */
void RingBuffer_Init(RingBuffer_t * rb, uint8_t * backing, size_t size);

/**
 * RingBuffer_Put
 *  Put a byte into the ring buffer.
 *
 * Param rb
 *  A pointer to the ring buffer to put the value into.
 *
 * Param val
 *  The value to put in the ring buffer.
 * 
 * Return
 *  True when the value has been inserted. False when there wasn't enough room.
 */
bool RingBuffer_Put(RingBuffer_t * rb, uint8_t val);

/**
 * RingBuffer_Get
 *  Pull a value out of the ring buffer.
 *
 * Param rb
 *  A pointer to the ring buffer to get the value from.
 *
 * Param val
 *  A pointer to a byte in which to store the extracted value.
 *
 * Return
 *  True when `val` points to a valid byte. False when there were no bytes to
 *  extract from the ring buffer.
 */
bool RingBuffer_Get(RingBuffer_t * rb, uint8_t * val);

/**
 * RingBuffer_Flush
 *  Empties the ring buffer.
 *
 * Param rb
 *  A pointer to the ring buffer to flush.
 */
void RingBuffer_Flush(RingBuffer_t * rb);

#endif // RingBuffer_H
