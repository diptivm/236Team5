#include "io2.h"                   // Good to self-reference
#include "main.h"                 // Application header
#include "msp430.h"               // Contains MSP430-specific definitions like P2DIR
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 
#include "msg.h"                // Req'd because we call MsgTS()


/******************************************************************************
****                                                                       ****
**                                                                           **
TaskIO()

**                                                                           **
****                                                                       ****
******************************************************************************/
void TaskIO(void) {
  MsgTS(STR_TASK_IO ": Starting.");

  while(1) {
    OS_Delay(100);
  }
}

/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED0() ClrLED0()

**                                                                           **
****                                                                       ****
******************************************************************************/
void ClrLED0(void) {
  P2DIR |=  BIT0;
  P2OUT &= ~BIT0;
}

void SetLED0(void) {
  P2DIR |= BIT0;
  P2OUT |= BIT0;
}

/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED1() ClrLED1()

**                                                                           **
****                                                                       ****
******************************************************************************/
void ClrLED1(void) {
  P2DIR |=  BIT1;
  P2OUT &= ~BIT1;
}

void SetLED1(void) {
  P2DIR |= BIT1;
  P2OUT |= BIT1;
}

/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED2() ClrLED2()

**                                                                           **
****                                                                       ****
******************************************************************************/
void ClrLED2(void) {
  P2DIR |=  BIT2;
  P2OUT &= ~BIT2;
}

void SetLED2(void) {
  P2DIR |= BIT2;
  P2OUT |= BIT2;
}


