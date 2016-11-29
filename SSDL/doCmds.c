#include "main.h"                 // Application header
#include "msp430.h"              //Req'd because we use WDTCTL 
#include "doCmds.h"              // Good to self-reference
#include "salvo.h"               // Req'd because we call e.g. OSDelay() 
#include "msg.h"                // Req'd because we call MsgTS()
#include "batt.h"

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
    BattState newChargeState = DIS_DEAD;

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
        sprintf(strTmp, STR_TASK_DO_CMDS " v: " VERSION_NUM " built on "__DATE__" at "__TIME__".");
        MsgTS(strTmp);
        break;

      case '1':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 1, setting BattState to CHRG_CC");
        MsgTS(strTmp);
        newChargeState = CHRG_CC;
        SetBattState(newChargeState);
        break;

      case '2':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 2, setting BattState to CHRG_CV");
        MsgTS(strTmp);
        newChargeState = CHRG_CV;
        SetBattState(newChargeState);
        break;

      case '3':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 3, setting BattState to CHRG_FLT");
        MsgTS(strTmp);
        newChargeState = CHRG_FLT;
        SetBattState(newChargeState);
        break;

      case '4':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 4, setting BattState to DIS_HI_V");
        MsgTS(strTmp);
        newChargeState = DIS_HI_V;
        SetBattState(newChargeState);
        break;

      case '5':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 5, setting BattState to DIS_MED_V");
        MsgTS(strTmp);
        newChargeState = DIS_MED_V;
        SetBattState(newChargeState);
        break;

      case '6':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 6, setting BattState to DIS_LO_V");
        MsgTS(strTmp);
        newChargeState = DIS_LO_V;
        SetBattState(newChargeState);
        break;

      case '7':
        sprintf(strTmp, STR_TASK_DO_CMDS ": Received 7, setting BattState to DIS_DEAD");
        MsgTS(strTmp);
        newChargeState = DIS_DEAD;
        SetBattState(newChargeState);
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
