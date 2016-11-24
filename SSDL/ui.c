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
  unsigned char inpChar;
  MsgTS(STR_TASK_UI ": Starting.");

  while(1) {
    //OS_Delay(200);
    OS_WaitSem(SEM_UI_CHAR, OSNO_TIMEOUT);
    inpChar = usart_uart1_getchar();
    sprintf(strTmp, STR_TASK_UI ": Hello from TaskUI. Read %d", inpChar);
    MsgTS(strTmp);

    switch(tolower(inpChar)) {
      case 'h':
      case '?':
        sprintf(strTmp, STR_TASK_UI ": Read h");
        MsgTS(strTmp);
        break;

      case 'i':
        sprintf(strTmp, STR_TASK_UI ": Read i");
        MsgTS(strTmp);
        break;
  
      case 'r':
        sprintf(strTmp, STR_TASK_UI ": Read r");
        MsgTS(strTmp);
        break;

      case 't':
        sprintf(strTmp, STR_TASK_UI ": Read t");
        MsgTS(strTmp);
        break;

      case 'v':
        sprintf(strTmp, STR_TASK_UI ": Read v");
        MsgTS(strTmp);
        break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        sprintf(strTmp, STR_TASK_UI ": Read number");
        MsgTS(strTmp);
        break;

      default:
        break;
    }
  }
}
