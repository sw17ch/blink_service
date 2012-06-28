#include "ProcessTasks.h"

#include "Blinker.h"

void ProcessTasks_Init(ProcessTasks_t * process_tasks)
{
  Blinker_Init(&process_tasks->blinker);
}

void ProcessTasks(ProcessTasks_t * process_tasks)
{
  Blinker_Service(&process_tasks->blinker);
}
