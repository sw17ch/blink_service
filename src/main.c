#include "main.h"
#include "Configure.h"    
#include "Initialize.h"
#include "ProcessTasks.h"

#include <avr/interrupt.h>
#include <avr/io.h>

ProcessTasks_t process_tasks;

int main(void)
{
  Configure();
  Initialize(&process_tasks);

  while(1)
  {
    ProcessTasks(&process_tasks);
  }

  return 0;
}

