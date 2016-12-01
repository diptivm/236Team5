#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call RtnBattVoltage()
#include "batt.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"                  // Req'd because we call MsgTS()
#include "io2.h"

/******************************************************************************
****                                                                       ****
**                                                                           **
TaskBatt()

**                                                                           **
****                                                                       ****
******************************************************************************/
//Module constants
#define VPROG_MAX               1.47    // VPROG in constant-current mode is 1.50V
#define CMOS_HI                 3.5 //CMOS high for determining whether USB is on
#define CHRG_FLOAT_LO           0.75    // -CHRG has a 30uA weak pull-down through 50k (5%) when
#define CHRG_FLOAT_HI           2.68    //   float mode is entered: 3.3V - ([15,50]uA * 50kOhm)

//State variable;
static BattState ChargeState = DIS_DEAD;
static OSgltypeTick chargingStartTicks = 0;

void TaskBatt(void) {
  float CHRG_level = RtnCHRG();
  float VBATT_level = RtnBattVoltage();
  float USB_level = Rtn5VUSB();
  char FaultState = 0;
  char ACPRState = 0;
  BattState newChargeState = DIS_DEAD;
  MsgTS(STR_TASK_BATT ": Starting.");
  while(1) {
    OS_Delay(200);

    //Sample the voltages when entering the loop.
    CHRG_level = RtnCHRG();
    VBATT_level = RtnBattVoltage();
    USB_level = Rtn5VUSB();
    FaultState = GetFault();
    ACPRState = GetACPR();

    
    //First check if USB is plugged in or not.
    if(USB_level > CMOS_HI){
      TurnChargerOn();
      if((ChargeState != CHRG_FLT) && (ChargeState != CHRG_CV) && (ChargeState != CHRG_CC)){
        OS_Delay(20); //Delay so that the charger has time to start up and clear ACPR and fault.
        chargingStartTicks = OSGetTicks();  // Tick corresponds to 10ms
      }

      if(CHRG_level < CHRG_FLOAT_LO){
        newChargeState = CHRG_CC;
      } else if(CHRG_level < CHRG_FLOAT_HI){
        newChargeState = CHRG_CV;
      } else{
        newChargeState = CHRG_FLT;
      }
      //Go to fault state if any of the fault conditions are indicated.
      if((ACPRState==0)||(FaultState==1)){
        newChargeState = FAULT;
      }
    } else {
      TurnChargerOff();
      if(VBATT_level < VBATT_NEARLY_DEAD){
        newChargeState = DIS_DEAD;
      }else if(VBATT_level < VBATT_PARTIALLY_CHARGED){
        newChargeState = DIS_LO_V;
      }else if(VBATT_level < VBATT_FULLY_CHARGED){
        newChargeState = DIS_MED_V;
      } else {
        newChargeState = DIS_HI_V;
      }
      ChargeState = newChargeState;
    }
  }
}

BattState GetBattState(void){
  return ChargeState;
}

//For testing: set the battery state
void SetBattState(BattState newState){
  ChargeState = newState;
}

OSgltypeTick GetChargeTime(void){
  if((ChargeState == CHRG_FLT) || (ChargeState == CHRG_CV) || (ChargeState == CHRG_CC)){
    return (OSGetTicks() - chargingStartTicks)/100;
   } else {
    return 0;
   }
}

