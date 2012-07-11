#ifndef Serial_Callbacks_H
#define Serial_Callbacks_H

#include <stdint.h>
#include <stdbool.h>

/*
 * !!!
 *
 * The implementations for these functions can be found in Serial.c
 *
 * !!!
 */

/**
 * Called by the UART driver when new data is available.
 */
void Serial_Callbacks_RX(uint8_t byte, void * param);

/**
 * Called by the UART driver when it can transmit more data.
 *
 * Returns true when the byte pointer is valid. False when it is invalid and
 * should not be transmitted.
 */
bool Serial_Callbacks_TX(uint8_t * byte, void * param);

#endif // Serial_Callbacks_H
