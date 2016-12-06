#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call RtnBattVoltage()
#include "batt.h"                 // Good to self-reference
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"                  // Req'd because we call MsgTS()
#include "io2.h"


//Module constants
/// Constant-current mode VPROG
#define VPROG_MAX               1.47  
/// CMOS high for determining whether USB is on  
#define CMOS_HI                 3.5
/// Low bound for the CV mode voltage of CHRG     
#define CHRG_FLOAT_LO           0.75    // -CHRG has a 30uA weak pull-down through 50k (5%) when
///High bound for the CV mode voltage of CHRG
#define CHRG_FLOAT_HI           2.68    //   float mode is entered: 3.3V - ([15,50]uA * 50kOhm)
///Full battery charge voltage
#define FINAL_FLOAT             4.15    // anything above this means we've reached final battery float voltage

//State variable;
static BattState ChargeState = DIS_DEAD;
static OSgltypeTick chargingStartTicks = 0;

///State machine for the battery charger.
/**
  This function is the Salvo task which runs every 200ms to update the
  state of the of the charger state machine and operate the charger accordingly. 
  It first checks whether the USB is plugged in to determine whether the charger should be on.
  If the USB power is on, the module turns on the charger and polls the CHRG pin to determine charge progress.
  If any of the fault indicators are on, the state machine will enter a fault state.
  If the USB power is off, the state machine will enter one of the battery level modes depending on the charge level.
*/
void TaskBatt(void) {
  float CHRG_level = RtnCHRG();
  float VBATT_level = RtnBattVoltage();
  float USB_level = Rtn5VUSB();
  char FaultState = 0;
  char ACPRState = 0;
  BattState newChargeState = DIS_DEAD;
  MsgTS(STR_TASK_BATT ": Starting.");
  OS_Delay(100);
  while(1) {
    OS_Delay(20);

    //Sample the voltages when entering the loop.
    CHRG_level = RtnCHRG();
    VBATT_level = RtnBattVoltage();
    USB_level = Rtn5VUSB();
    FaultState = GetFault();
    ACPRState = GetACPR();

    
    //First check if USB is plugged in or not.
    if(USB_level > CMOS_HI){
      TurnChargerOn();
      TurnRegulatorOff();
      if((ChargeState != CHRG_FLT) && (ChargeState != CHRG_CV) && (ChargeState != CHRG_CC)){
        OS_Delay(20); //Delay so that the charger has time to start up and clear ACPR and fault.
        chargingStartTicks = OSGetTicks();  // Tick corresponds to 10ms
      }
      if(CHRG_level > CHRG_FLOAT_HI){
        newChargeState = CHRG_FLT;
      } else if(CHRG_level < CHRG_FLOAT_LO){
        newChargeState = CHRG_CC;
      } else{
        newChargeState = CHRG_CV;
      } 
      //Go to fault state if any of the fault conditions are indicated.
      if((ACPRState==1)||(FaultState==0)){
        newChargeState = FAULT;
      }
    } else {
      TurnChargerOff();
      TurnRegulatorOn();
      if(VBATT_level < VBATT_NEARLY_DEAD){
        newChargeState = DIS_DEAD;
      }else if(VBATT_level < VBATT_PARTIALLY_CHARGED){
        newChargeState = DIS_LO_V;
      }else if(VBATT_level < VBATT_FULLY_CHARGED){
        newChargeState = DIS_MED_V;
      } else {
        newChargeState = DIS_HI_V;
      }
    }
    ChargeState = newChargeState;
  }
}

///State getter
/**
  Used to get the value of the private state variable.
  \return The charger state.
*/
BattState GetBattState(void){
  return ChargeState;
}

///State setter
/**
  Function to set the value of the private state variable.
  To be used while testing.
  \param newState The desired charger state
*/
void SetBattState(BattState newState){
  ChargeState = newState;
}

///Charge time getter
/**
  Gets the number of ticks since the last time the charger was plugged in.
  \return The number of OS ticks since charging was started
*/
OSgltypeTick GetChargeTime(void){
  if((ChargeState == CHRG_FLT) || (ChargeState == CHRG_CV) || (ChargeState == CHRG_CC)){
    return (OSGetTicks() - chargingStartTicks)/100;
   } else {
    return 0;
   }
}

