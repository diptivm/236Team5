#ifndef __io2_h
#define __io2_h
/**
/******************************************************************************
****                                                                       ****
**                                                                           **
Functions available to all who include io.h

**                                                                           **
****                                                                       ****
*******************************************************************************
*/
extern void TaskIO(void);
extern void SetLED0(void);
extern void ClrLED0(void);
extern void SetLED1(void);
extern void ClrLED1(void);
extern void SetLED2(void);
extern void ClrLED2(void);
extern void TurnChargerOn(void);
extern void TurnChargerOff(void);
extern void TurnRegulatorOn(void);
extern void TurnRegulatorOff(void);
extern char GetACPR(void);
extern char GetFault(void);
extern char GetRegulatorState(void);

#define STR_TASK_IO  "TaskIO"

#endif /* __io2_h */
