#include <stdio.h>
#include <string.h>
#include "adc.h"                  // Req'd because we call various adc functions for on-chip temp, voltages etc.
#include "batt.h"                 // Req'd because we call GetChargeTime()
#include "io2.h"                  //Req'd because we call GetACPR() and GetFault()
#include "main.h"                 // Application header
#include "msg.h"                  // Req'd because we call MsgTS()
#include "telem.h"                 // Good to self-reference

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
telemDisplay()

Function that printstelemetry collected by the system in a readable format, 
including voltages, currents and status information as shown below:

+5V_USB          x.xxV       Signal SNS_USB
charge time    xxxxx s       Time elapsed since charging started

MCU              x.xxV       Signal VCC_MCU 
VCC              x.xxV       SNS_VCC
VCC Current   xxxxx mA       Calculated VCC current
temp               xxC       On-chip temperature
 
Batt:            x.xxV      Signal SNS_BATT
PROG:            x.xxV      Signal SNS_PROG
CHRG:            x.xxV      Signal SNS_CHRG
-ACPR:          1 or 0      -ACPR bit
-FAULT:         1 or 0      -FAULT bit

Input Parameters: None
Outputs: None
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
void telemDisplay(void) {
  sprintf(strTmp + strlen(strTmp), "  +5V_USB: %.2fV  charge time: %5lus", Rtn5VUSB(), GetChargeTime());
  MsgTS(strTmp);
  sprintf(strTmp, "  MCU:  %.2fV   VCC:  %.2fV   VCC current: %5.0f mA temp: %2uC", RtnVCCMCU(), RtnVCC(), RtnVCCCurrent(), RtnOnChipTemp());
  MsgTS(strTmp);
  sprintf(strTmp, "  Batt: %.2fV   PROG: %.2fV   CHRG:%.2fV    -ACPR:%i  -FAULT:%i", RtnBattVoltage(), RtnPROG(), RtnCHRG(), GetACPR(), GetFault());
  MsgTS(strTmp);
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
tempDisplay()

Function that returns on-chip temperature collected by the ADC as an unsigned 
integer.

Input Parameters: None
Outputs: unsigned int temperature
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
unsigned int tempDisplay(void) {
  return RtnOnChipTemp();
}
