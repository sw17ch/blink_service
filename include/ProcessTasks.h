#ifndef ProcessTasks_H
#define ProcessTasks_H

#include "Blinker.h"
#include "Echo.h"

#define UART_BAUD_RATE (115200)

typedef struct {
  Blinker_t blinker;
  Echo_t echo;
  Serial_t serial;
} ProcessTasks_t;

void ProcessTasks_Init(ProcessTasks_t * process_tasks);
void ProcessTasks(ProcessTasks_t * process_tasks);

#endif // ProcessTasks_H
