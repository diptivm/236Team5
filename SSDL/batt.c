#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call RtnBattVoltage()
#include "batt.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"    // Req'd because we call usart_uart1_msg_ts()


/******************************************************************************
****                                                                       ****
**                                                                           **
TaskBatt()

**                                                                           **
****                                                                       ****
******************************************************************************/
void TaskBatt(void) {
  MsgTS(STR_TASK_BATT ": Starting.");

  while(1) {
    OS_Delay(200);
    sprintf(strTmp, STR_TASK_BATT ": Battery Voltage is %.2fV", RtnBattVoltage());
    MsgTS(strTmp);
  }
}
