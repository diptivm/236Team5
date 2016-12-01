#include <stdio.h>
#include <string.h>
#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call various adc functions for on-chip temp, voltages etc.
#include "telem.h"                 // Good to self-reference
#include "msg.h"                  // Req'd because we call MsgTS()
#include "batt.h"                 // Req'd because we call GetChargeTime()


void telemDisplay(void) {
  sprintf(strTmp + strlen(strTmp), "+5V_USB: %.2fV charge time: %ds", Rtn5VUSB(), GetChargeTime());
  MsgTS(strTmp);
  sprintf(strTmp, "MCU: %.2fV VCC: %.2fV VCC temp: %uC", RtnVCCMCU(), RtnVCC(), RtnOnChipTemp());
  MsgTS(strTmp);
  sprintf(strTmp, "Batt: %.2fV PROG: %.2f CHRG:%.2f", RtnBattVoltage(), RtnPROG(), RtnCHRG());
  MsgTS(strTmp);
}

unsigned int tempDisplay(void) {
  return RtnOnChipTemp();
}
