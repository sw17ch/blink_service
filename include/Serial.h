#ifndef SERIAL_H
#define SERIAL_H

#include "RingBuffer.h"

#include <stdint.h>

#define RING_BUFFER_BACKING_SIZE (32)

typedef struct {
  RingBuffer_t tx_rb;
  RingBuffer_t rx_rb;
  uint8_t tx_rb_backing[RING_BUFFER_BACKING_SIZE];
  uint8_t rx_rb_backing[RING_BUFFER_BACKING_SIZE];
} Serial_t;

/**
 * Initializes UART0 to be the serial port.
 */
void Serial_Init(Serial_t * serial);

/**
 * Adds a sequence of bytes to be sent over the serial port.
 */
size_t Serial_Put(Serial_t * serial, uint8_t * bytes, size_t len);

/**
 * Gets a sequence of bytes from the serial port queue.
 *
 * Returns the number of valid bytes in `bytes`.
 */
size_t Serial_Get(Serial_t * serial, uint8_t * bytes, size_t len);

#endif /* SERIAL_H */
