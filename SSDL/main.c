#include <__cross_studio_io.h>    // for CrossStudio debugging
#include "adc.h"                  // Req'd because we reference TaskADC()
#include "batt.h"                 // Req'd because we reference TaskBatt()
#include "init.h"                 // Req'd because we call Init()
#include "io2.h"                   // Req'd because we reference TaskIO()
#include "led.h"                  // Req'd because we reference TaskLED()
#include "main.h"                 // Application header
#include "salvo.h"                // Req'd because we call e.g. OSInit() 
#include "ui.h"                   // Req'd because we reference TaskUI()
#include "usart_uart.h"           // Req'd because we call usart_uart1_puts()
#include "msg.h"                  // Req'd because we call MsgTS()


/**
/******************************************************************************
****                                                                       ****
**                                                                           **
Global variables used by any module in the application
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
char strTmp[256];  // General-purpose buffer for creating long strings


/**
/******************************************************************************
****                                                                       ****
**                                                                           **
main() function for the program. 

Prints a startup message with version number and date/time of build.
Creates the Salvo tasks and events required by the program.
Enables interrupts.
Starts the OS Scheduler.

Tasks created: TaskADC, TaskBatt, TaskIO, TaskUI, TaskLED
Events created: Semaphore (SEM_UI_CHAR)

Input arguments: None.
Output: None.
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
void main(void) {

  Init();

  // Now that the non-RTOS stuff has been initialized, we can output via USB.
  usart_uart1_puts("\r\n");
  MsgTS("main: SSDL Team XXX AA236A 1617 Homework Assignment #2");
  MsgTS("  v" VERSION_NUM " built on "__DATE__" at "__TIME__"."); // note indent of two spaces

  // Initialize the RTOS.
  OSInit();
  
  OSCreateSem(SEM_UI_CHAR, 0);

  // Create the various tasks.
  OSCreateTask(TaskADC,        OSTCBP(1),  3);
  OSCreateTask(TaskBatt,       OSTCBP(2),  4);
  OSCreateTask(TaskIO,         OSTCBP(3),  11);
  OSCreateTask(TaskUI,         OSTCBP(4),  11);
  OSCreateTask(TaskLED,        OSTCBP(5),  11);

  // Since ISRs are present, we must enable interrupts globally. No need to touch interrupts again.
  __enable_interrupt();

  // OK to use, but keep in mind that it has weird run-time effects and requires that the FET
  //  be present
//  debug_printf("main: This is debug output in the CrossWorks IDE Debug I/O Terminal.\n");

  // Run the scheduler open-loop for best performance.
  while(1) {
    OSSched();
  }

  // We never reach this.
  debug_exit(0);
}

