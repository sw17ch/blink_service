#include "Serial.h"
#include "Serial_Callbacks.h"
#include "UART.h"

void Serial_Init(Serial_t * serial)
{
  RingBuffer_Init(&serial->tx_rb, serial->tx_rb_backing, sizeof(serial->tx_rb_backing));
  RingBuffer_Init(&serial->rx_rb, serial->rx_rb_backing, sizeof(serial->rx_rb_backing));
  UART_Init(Serial_Callbacks_RX, (void *)serial,
            Serial_Callbacks_TX, (void *)serial);
}

size_t Serial_Put(Serial_t * serial, uint8_t * bytes, size_t len)
{
  size_t remaining = len;
  size_t i = 0;

  while(0 < remaining)
  {
    if(RingBuffer_Put(&serial->tx_rb, bytes[i]))
    {
      i++;
      remaining--;
    }
    else
    {
      break;
    }
  }

  if (i > 0)
  {
    UART_Wakeup();
  }

  return remaining;
}

size_t Serial_Get(Serial_t * serial, uint8_t * bytes, size_t len)
{
  uint8_t byte;
  size_t gotten;

  for (gotten = 0; gotten < len; gotten++)
  {
    if(RingBuffer_Get(&serial->rx_rb, &byte))
    {
      bytes[gotten] = byte;
    }
    else
    {
      break;
    }
  }

  return gotten;
}

void Serial_Callbacks_RX(uint8_t byte, void * param)
{
  Serial_t * serial = (Serial_t *)param;
  RingBuffer_Put(&serial->rx_rb, byte); // currently not checking for overflow
}

bool Serial_Callbacks_TX(uint8_t * byte, void * param)
{
  Serial_t * serial = (Serial_t *)param;
  return RingBuffer_Get(&serial->tx_rb, byte);
}
