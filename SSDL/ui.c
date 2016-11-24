#include "main.h"                 // Application header
#include "ui.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"    // Req'd because we call usart_uart1_msg_ts()
#include "doCmds.h"                 // Req'd because we call setCmd()


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
        setCmd('h');
        break;

      case 'i':
        setCmd('i');
        break;
  
      case 'r':
        setCmd('r');
        break;

      case 't':
        setCmd('t');
        break;

      case 'v':
        setCmd('v');
        break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        setCmd(inpChar); //The cmd index to dispatch is simply inpChar
        break;

      default:
        break;
    }
  }
}
