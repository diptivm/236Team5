#include "main.h"                 // Application header
#include "adc.h"                  // Req'd because we call various adc functions for on-chip temp, voltages etc.
#include "telem.h"                 // Good to self-reference
#include "msg.h"                  // Req'd because we call MsgTS()

void telemDisplay(void) {

}

unsigned int tempDisplay(void) {
  return RtnOnChipTemp();
}