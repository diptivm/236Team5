#include "io2.h"                   // Good to self-reference
#include "main.h"                 // Application header
#include "msg.h"                  // Req'd because we call MsgTS()
#include "msp430.h"               // Contains MSP430-specific definitions like P2DIR
#include "salvo.h"                // Req'd because we call e.g. OSDelay() 


static char RegulatorState = 1;

/**
TaskIO()

Task that prints a message when it starts, and then idles.

Input parameters: none
\param none
Outputs: none
\return The number of OS ticks since charging was started
*/
void TaskIO(void) {
  MsgTS(STR_TASK_IO ": Starting.");

  while(1) {
    OS_Delay(100);
  }
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED0() ClrLED0()

Functions that control the state of LED0.

Input parameters: none
Outputs: none
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
void ClrLED0(void) {
  P2DIR |=  BIT0;
  P2OUT &= ~BIT0;
}

void SetLED0(void) {
  P2DIR |= BIT0;
  P2OUT |= BIT0;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED1() ClrLED1()

Functions that control the state of LED1.

Input parameters: none
Outputs: none
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
void ClrLED1(void) {
  P2DIR |=  BIT1;
  P2OUT &= ~BIT1;
}

void SetLED1(void) {
  P2DIR |= BIT1;
  P2OUT |= BIT1;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
SetLED2() ClrLED2()

Functions that control the state of LED2.

Input parameters: none
Outputs: none
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
void ClrLED2(void) {
  P2DIR |=  BIT2;
  P2OUT &= ~BIT2;
}

void SetLED2(void) {
  P2DIR |= BIT2;
  P2OUT |= BIT2;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
TurnChargerOn() TurnChargerOff()

Functions that control the state of the charger

Input parameters: none
Outputs: none
**                                                                           **
****                                                                       ****
*******************************************************************************
*/

void TurnChargerOn(void){
  P2DIR |= BIT3|BIT4;
  P2OUT |= BIT3|BIT4;
}

void TurnChargerOff(void){
  P2DIR |= BIT3|BIT4;
  P2OUT &= (~BIT3)&(~BIT4);  
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
TurnRegulatorOn() TurnRegulatorOff()

Functions that control the state of the regulator.

Input parameters: none
Outputs: none
**                                                                           **
****                                                                       ****
*******************************************************************************
*/

void TurnRegulatorOff(void){
  P2DIR |= BIT5;
  P2OUT |= BIT5;
  RegulatorState = 0;
}

void TurnRegulatorOn(void){
  P2DIR |= BIT5;
  P2OUT &= (~BIT5);
  RegulatorState = 1;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
GetACPR()

Function that returns the ACPR bit, which indicates whether the AC power is
connected.

Input parameters: none
Outputs: char ACPR
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
char GetACPR(void) {
//  P2DIR &=  ~BIT6;
//  if(P2IN&BIT6 > 0){
//    return 0;
//  } else {
//    return 1;
//  }
  char a;
  P2DIR &= ~BIT6;
  a=(P2IN&BIT6)>>6;
  return a;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
GetFault()

Function that returns the FAULT bit, which indicates whether a fault has
occurred during charging.

Input parameters: none
Outputs: char FAULT
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
char GetFault(void) {
//  P2DIR &=  ~BIT7;
//  if(P2IN&BIT7 > 0){
//    return 0;
//  } else {
//    return 1;
//  }
  char a;
  P2DIR &= ~BIT7;
  a=(P2IN&BIT7)>>7;
  return a;
}

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
GetRegulatorState()

Function that returns the state of the regulator

Input parameters: none
Outputs: char RegulatorState
**                                                                           **
****                                                                       ****
*******************************************************************************
*/
char GetRegulatorState(void){
  return RegulatorState;
}
