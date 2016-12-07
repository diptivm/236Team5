#include "adc.h"                  // Req'd because we call RtnBattVoltage()
#include "batt.h"                 // Req'd because we call on battery state
#include "io2.h"                  // Req'd because we call SetLED0(), etc.
#include "led.h"                  // Good to self-reference
#include "main.h"                 // Application header
#include "msg.h"                  // Req'd because we call MsgTS()
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 

/**

TaskLED()

Task that sets the three-LED bar graph based on the current battery voltage,
updated at a frequency of 0.5 Hz. The ON duty cycle for the LEDs is 50% when the
battery is charging ("blinking"), and 10% when the battery is discharging
("flashing"). It uses the getBattState() function defined in batt.c to grab the
current state of the battery to determine which LEDs need to be turned on/off 
using the SetLED and ClrLED functions defined in io2.c.

Input argument: None
<br>Output: None


*/

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

      case FAULT :
        SetLED1();
        OS_Delay(10);
        ClrLED1();
        OS_Delay(90);
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

      default:
         break;

    }
  }
}
