#include "UART.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/**
 * Lets talk about registers for UART0.
 *
 *  UBRR0H and UBRR0L
 *    These represent the high bits and low bits of the Baud Rate for UART0.
 *    UBRR0L represents bits 0:7 of the baud rate while UBRRH represents bits
 *    8:11 (bits 12:15 are unused).
 *
 *    Baud Rate is represented as a 12-bit value.
 *
 *  UCSR0A, UCSR0B, and UCSR0C
 *    These are the USART Control and Status Registers for UART0. These do
 *    silly things like tell is if a receive is complete or allow us to enable
 *    interrupts for different actions.
 *
 *  UDR0
 *    This register is used for both the transmission and reception of data.
 *    Yep, it does both. Awesome.
 */

#define TX_IN_PROGRESS() (UCSR0A & _BV(TXC0))
#define TX_IDLE() (!TX_IN_PROGRESS())

static void Tx_Byte(void);

typedef struct {
  UART_RX_t rx_cb;
  UART_TX_t tx_cb;
  bool running;
} UART_Driver_t;

static UART_Driver_t uart_driver = { 0 };

void UART_Init(UART_RX_t rx_cb, UART_TX_t tx_cb)
{
  uart_driver.rx_cb = rx_cb;
  uart_driver.tx_cb = tx_cb;

  UCSR0A |= _BV(U2X0); // Double USART transmission speed
}

void UART_Start(uint32_t baud)
{
  uint16_t ubrr = (F_CPU / (8 * baud)) - 1;
  UBRR0H = (uint8_t)(0x0F & (ubrr >> 8));
  UBRR0L = (uint8_t)(0xFF & ubrr);

  UCSR0B |= _BV(RXEN0);  // Enable RX
  UCSR0B |= _BV(TXEN0);  // Enable TX
  UCSR0B |= _BV(RXCIE0); // Enable RX Complete interrupt
  UCSR0B |= _BV(TXCIE0); // Enable TX Complete interrupt

  uart_driver.running = true;
}

void UART_Stop(void)
{
  UCSR0B &= ~_BV(RXEN0);  // Disable RX
  UCSR0B &= ~_BV(TXEN0);  // Disable TX
  UCSR0B &= ~_BV(RXCIE0); // Disable RX Complete interrupt
  UCSR0B &= ~_BV(TXCIE0); // Disable TX Complete interrupt

  uart_driver.running = false;
}

void UART_Wakeup(void)
{
	cli(); // Disable interrupts
  if(TX_IDLE())
	{
		Tx_Byte();
	}
	sei(); // Enable interrupts
}

bool UART_IsRunning(void)
{
  return uart_driver.running;
}

SIGNAL(USART_RX_vect)
{
  uint8_t c = UDR0;
  uart_driver.rx_cb(c);
}

SIGNAL(USART_TX_vect)
{
  Tx_Byte();
}


static void Tx_Byte(void)
{
  uint8_t c;
  if(uart_driver.tx_cb(&c))
  {
    UDR0 = c;
  }
}
