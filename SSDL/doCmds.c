#include "main.h"                 // Application header
#include "doCmds.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"    // Req'd because we call usart_uart1_msg_ts()


/******************************************************************************
****                                                                       ****
**                                                                           **
TaskDoCmds()

**                                                                           **
****                                                                       ****
******************************************************************************/
void TaskDoCmds(void) {
  MsgTS(STR_TASK_DO_CMDS ": Starting.");

  while(1) {
    OS_Delay(200);
    sprintf(strTmp, STR_TASK_DO_CMDS ": Hello from TakskDoCmds");
    MsgTS(strTmp);
  }
}
