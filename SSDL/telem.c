#include <stdio.h>
#include <string.h>
#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call various adc functions for on-chip temp, voltages etc.
#include "telem.h"                 // Good to self-reference
#include "msg.h"                  // Req'd because we call MsgTS()
#include "batt.h"                 // Req'd because we call GetChargeTime()
#include "io2.h"


void telemDisplay(void) {
  sprintf(strTmp + strlen(strTmp), "  +5V_USB: %.2fV  charge time: %5lus", Rtn5VUSB(), GetChargeTime());
  MsgTS(strTmp);
  sprintf(strTmp, "  MCU:  %.2fV   VCC:  %.2fV   VCC current: %5.0f mA temp: %2uC", RtnVCCMCU(), RtnVCC(), RtnVCCCurrent(), RtnOnChipTemp());
  MsgTS(strTmp);
  sprintf(strTmp, "  Batt: %.2fV   PROG: %.2fV   CHRG:%.2fV    -ACPR:%i  -FAULT:%i", RtnBattVoltage(), RtnPROG(), RtnCHRG(), GetACPR(), GetFault());
  MsgTS(strTmp);
}

unsigned int tempDisplay(void) {
  return RtnOnChipTemp();
}
