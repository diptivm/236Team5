#include "main.h"                 // Application header
#include "ui.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"    // Req'd because we call usart_uart1_msg_ts()


/******************************************************************************
****                                                                       ****
**                                                                           **
TaskUI()

**                                                                           **
****                                                                       ****
******************************************************************************/
void TaskUI(void) {
  MsgTS(STR_TASK_UI ": Starting.");

  while(1) {
    OS_Delay(200);
    sprintf(strTmp, STR_TASK_UI ": Hello from TaskUI");
    MsgTS(strTmp);
  }
}
