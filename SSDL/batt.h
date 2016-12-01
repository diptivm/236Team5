/******************************************************************************
****                                                                       ****
**                                                                           **
Functions available to all who include batt.h

**                                                                           **
****                                                                       ****
******************************************************************************/

#ifndef __BATT_H
#define __BATT_H

#include "salvo.h"                // Req'd because we use OSgltypeTick

extern void TaskBatt(void);

typedef enum {CHRG_CC, CHRG_CV, CHRG_FLT, DIS_HI_V, DIS_MED_V, DIS_LO_V, DIS_DEAD} BattState;
extern BattState GetBattState(void);
extern void SetBattState(BattState);
extern OSgltypeTick GetChargeTime(void); 

#define STR_TASK_BATT   "TaskBatt"
#endif
