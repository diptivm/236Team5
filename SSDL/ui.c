#include <ctype.h>
#include "batt.h"                 //Req'd because we use several variables and functions related to battery state
#include "main.h"                 // Application header
#include "msp430.h"              //Req'd because we use WDTCTL 
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "telem.h"               // Req'd because we call tempDisplay() and telemDisplay()
#include "ui.h"                 // Good to self-reference
#include "usart_uart.h"           //Req'd because we call usart_uart1_getchar()
#include "msg.h"                  // Req'd because we call MsgTS()

/**

TaskUI()

Task that controls the text UI by processing incoming one-letter commands and
responding where necessary. Task_UI waits on a semaphore that is signaled by 
the Rx ISR when a key-press is received. It then requests the input char from 
the usart_uart1_getchar() function provided in the Pumpkin libraries for MSP430
and uses a switch case on this char to decide on the action to perform.
<br>Commands supported are - 
<br>h/H/?: help(lists commands)
<br>i/I: status information
<br>r/R: reset (restart program)
<br>t/T: display on-chip temperature
<br>v/V: display version
<br>1: switch to battery state CHRG_CC
<br>2: switch to battery state CHRG_CV
<br>3: switch to battery state CHRG_FLT
<br>4: switch to battery state DIS_HI_V
<br>5: switch to battery state DIS_MED_V
<br>6: switch to battery state DIS_LO_V
<br>7: switch to battery state DIS_DEAD
<br>S: display battery state number

Input Parameters: None
<br>Outputs: None

*/
void TaskUI(void) {
  char battState;  
  BattState newChargeState;
  unsigned char inpChar;
  MsgTS(STR_TASK_UI ": Starting.");

  while(1) {
    //OS_Delay(200);
    OS_WaitSem(SEM_UI_CHAR, OSNO_TIMEOUT);
    inpChar = usart_uart1_getchar();
//    sprintf(strTmp, STR_TASK_UI ": Hello from TaskUI. Read %d", inpChar);
//    MsgTS(strTmp);

    switch(tolower(inpChar)) {
      case 'h':
      case '?':
        sprintf(strTmp, STR_TASK_UI ": h|?: Commands: {h|?, i, r, t, v, 1-7}");
        MsgTS(strTmp);
        break;

      case 'i':
        sprintf(strTmp, STR_TASK_UI ": i: System Info: ");
        //MsgTS(strTmp);
        telemDisplay();
        break;
  
      case 'r':
        sprintf(strTmp, STR_TASK_UI ": r: Reset (via WDT) in 1s");
        MsgTS(strTmp);
        OS_Delay(100);
        WDTCTL = 0xDEAD;
        break;

      case 't':
        sprintf(strTmp, STR_TASK_UI ": t: On-chip temperature is %u C", tempDisplay());
        MsgTS(strTmp);
        break;

      case 'v':
        sprintf(strTmp, STR_TASK_UI ": v: " VERSION_NUM " built on "__DATE__" at "__TIME__".");
        MsgTS(strTmp);
        break;

     case '1':
        sprintf(strTmp, STR_TASK_UI ": Received 1, setting BattState to CHRG_CC");
        MsgTS(strTmp);
        newChargeState = CHRG_CC;
        SetBattState(newChargeState);
        break;

      case '2':
        sprintf(strTmp, STR_TASK_UI ": Received 2, setting BattState to CHRG_CV");
        MsgTS(strTmp);
        newChargeState = CHRG_CV;
        SetBattState(newChargeState);
        break;

      case '3':
        sprintf(strTmp, STR_TASK_UI ": Received 3, setting BattState to CHRG_FLT");
        MsgTS(strTmp);
        newChargeState = CHRG_FLT;
        SetBattState(newChargeState);
        break;

      case '4':
        sprintf(strTmp, STR_TASK_UI ": Received 4, setting BattState to DIS_HI_V");
        MsgTS(strTmp);
        newChargeState = DIS_HI_V;
        SetBattState(newChargeState);
        break;

      case '5':
        sprintf(strTmp, STR_TASK_UI ": Received 5, setting BattState to DIS_MED_V");
        MsgTS(strTmp);
        newChargeState = DIS_MED_V;
        SetBattState(newChargeState);
        break;

      case '6':
        sprintf(strTmp, STR_TASK_UI ": Received 6, setting BattState to DIS_LO_V");
        MsgTS(strTmp);
        newChargeState = DIS_LO_V;
        SetBattState(newChargeState);
        break;

      case '7':
        sprintf(strTmp, STR_TASK_UI ": Received 7, setting BattState to DIS_DEAD");
        MsgTS(strTmp);
        newChargeState = DIS_DEAD;
        SetBattState(newChargeState);
        break;

      case '0':
        //do nothing: by default
        break;

      case 's':
        battState = (char) GetBattState();
        sprintf(strTmp, STR_TASK_UI ": BattState is %u", battState);
        MsgTS(strTmp);
        break;

      default:
        sprintf(strTmp, STR_TASK_UI ": Invalid command. Press h for help.");
        MsgTS(strTmp);
        break;
    }
  }
}
