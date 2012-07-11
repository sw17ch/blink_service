#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

#ifndef UART_COUNT
  #define UART_COUNT (1)
#endif

/**
 * UART_RX_t
 *  Callback used by the UART driver when it has new data.
 *
 *  Param data
 *    The data that was received.
 *
 *  Param param
 *		A user specified pointer to be passed to the callback.
 */
typedef void (*UART_RX_t) (uint8_t data, void * param);

/**
 * UART_TX_t
 *  Callback used by the UART when it is ready to transmit more data.
 * 
 *  Param byte
 *    Pointer to a byte in which the callback function should store the next
 *    byte to be transmitted.
 *
 *    The pointer will always point to valid data.
 *
 *  Param param
 *		A user specified pointer to be passed to the callback.
 *
 *  Return
 *    True when the byte parameter points to a valid byte to be transmitted.
 *    False when the byte parameter does not point to valid data.
 */
typedef bool (*UART_TX_t) (uint8_t * byte, void * param);

/**
 * UART_Init
 *  Initialization function for the UART.
 *
 *  Param rx_cb
 *    The receive callback to use.
 *
 *  Param tx_cb
 *    The transmit callback to use.
 */
void UART_Init(UART_RX_t rx_cb, void * rx_param, UART_TX_t tx_cb, void * tx_param);

/**
 * UART_Start
 *  Begin operation of UART0. It will be use the following configuration:
 *    - 8 data bits
 *    - 0 parity bits
 *    - 1 stop bit
 *
 *  Param baud
 *    The baud rate at which to operate the port.
 */
void UART_Start(uint32_t baud);

/**
 * UART_Stop
 *  Cease operation of the serial port.
 */
void UART_Stop(void);

/**
 * UART_Wakeup
 *  Ask the UART driver to attempt to transmit additional bytes. This will
 *  service the transmission callback until it returns false;
 */
void UART_Wakeup(void);

/**
 * UART_IsRunning
 *  True when the UART has been started.
 */
bool UART_IsRunning(void);

#endif /* UART_H */
