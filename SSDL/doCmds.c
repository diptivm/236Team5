#include "main.h"                 // Application header
#include "msp430.h"              //Req'd because we use WDTCTL 
#include "doCmds.h"              // Good to self-reference
#include "salvo.h"               // Req'd because we call e.g. OSDelay() 
#include "msg.h"                // Req'd because we call usart_uart1_msg_ts()

unsigned char cmd = 0;

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
    sprintf(strTmp, STR_TASK_DO_CMDS ": TakskDoCmds has cmd = %d", cmd);
    MsgTS(strTmp);

    switch(tolower(cmd)) {
      case 'h':
        sprintf(strTmp, STR_TASK_DO_CMDS ": h|?: Commands: {h|?, i, r, t, v, 1-7}");
        MsgTS(strTmp);
        break;

      case 'i':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received i");
        MsgTS(strTmp);
        break;
  
      case 'r':
        sprintf(strTmp, STR_TASK_DO_CMDS " r: Reset (via WDT) in 1s");
        MsgTS(strTmp);
        OS_Delay(100);
        WDTCTL = 0xDEAD;
        break;

      case 't':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received t");
        MsgTS(strTmp);
        break;

      case 'v':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received v");
        MsgTS(strTmp);
        break;

      case '1':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 1");
        MsgTS(strTmp);
        break;

      case '2':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 2");
        MsgTS(strTmp);
        break;

      case '3':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 3");
        MsgTS(strTmp);
        break;

      case '4':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 4");
        MsgTS(strTmp);
        break;

      case '5':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 5");
        MsgTS(strTmp);
        break;

      case '6':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 6");
        MsgTS(strTmp);
        break;

      case '7':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 7");
        MsgTS(strTmp);
        break;

      case '0':
        //do nothing: by default
        break;

      default:
        break;
    }

    cmd = 0;
  }
}

void setCmd(unsigned char newCmd) {
  cmd = newCmd;
}