#ifndef ProcessTasks_H
#define ProcessTasks_H

#include "Blinker.h"

typedef struct {
  Blinker_t blinker;
} ProcessTasks_t;

void ProcessTasks_Init(ProcessTasks_t * process_tasks);
void ProcessTasks(ProcessTasks_t * process_tasks);

#endif // ProcessTasks_H
