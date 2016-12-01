#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call RtnBattVoltage()
#include "batt.h"                 // Req'd because we call on battery state
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "io2.h"                  // Req'd because we call SetLED0(), etc.
#include "led.h"                  // Good to self-reference
#include "msg.h"                  // Req'd because we call MsgTS()

/******************************************************************************
****                                                                       ****
**                                                                           **
TaskLED()

**                                                                           **
****                                                                       ****
******************************************************************************/
void TaskLED(void) {
  BattState batt_state;
  MsgTS(STR_TASK_LED ": Starting.");

  while(1){

    batt_state = GetBattState();
    switch(batt_state){

      case CHRG_CC :
        SetLED0();
        OS_Delay(50);
        ClrLED0();
        OS_Delay(50);
        break;

      case CHRG_CV :
        SetLED0();
        SetLED1();
        OS_Delay(50);
        ClrLED0();
        ClrLED1();
        OS_Delay(50);
        break;

      case CHRG_FLT :
        SetLED0();
        SetLED1();
        SetLED2();
        OS_Delay(50);
        ClrLED0();
        ClrLED1();
        ClrLED2();
        OS_Delay(50);
        break;

      case DIS_DEAD :
        OS_Delay(100);
        break;

      case DIS_LO_V :
        SetLED0();
        OS_Delay(10);
        ClrLED0();
        OS_Delay(90);
        break;

      case DIS_MED_V :
        SetLED0();
        SetLED1();
        OS_Delay(10);
        ClrLED0();
        ClrLED1();
        OS_Delay(90);
        break;

      case DIS_HI_V :
        SetLED0();
        SetLED1();
        SetLED2();
        OS_Delay(10);
        ClrLED0();
        ClrLED1();
        ClrLED2();
        OS_Delay(90);
        break;
      //OS_Delay(100);
      default:
         break;

    }
  }
}
