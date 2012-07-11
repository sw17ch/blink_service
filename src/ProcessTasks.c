#include "ProcessTasks.h"

#include "Blinker.h"
#include "Echo.h"
#include "Serial.h"
#include "UART.h"

void ProcessTasks_Init(ProcessTasks_t * process_tasks)
{
  Serial_Init(&process_tasks->serial);
  UART_Start(UART_BAUD_RATE);

  Blinker_Init(&process_tasks->blinker);
  Echo_Init(&process_tasks->echo);
}

void ProcessTasks(ProcessTasks_t * process_tasks)
{
  Blinker_Service(&process_tasks->blinker);
  Echo_Service(&process_tasks->echo, &process_tasks->serial);
}
