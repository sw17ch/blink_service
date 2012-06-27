#include "ProcessTasks.h"

#include "Blinker.h"

void ProcessTasks(ProcessTasks_t * process_tasks)
{
  Blinker_Service(&process_tasks->blinker);
}
