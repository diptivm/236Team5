/**
\file batt.h Functions available to all who include batt.h
*/

#ifndef __BATT_H
#define __BATT_H

#include "salvo.h" // Req'd because we use OSgltypeTick

extern void TaskBatt(void);

typedef enum {
	///Charging at constant current mode
	CHRG_CC, 
	///Charging at constant voltage charge mode
	CHRG_CV, 
	///Charging finished
	CHRG_FLT, 
	///Discharging at battery voltage above 4.13V
	DIS_HI_V, 
	///Discharging at battery voltage between 3.6V and 4.13V
	DIS_MED_V, 
	///Discharging at battery voltage between 2.90V and 3.6V
	DIS_LO_V, 
	///Discharging at battery voltage below 2.90V
	DIS_DEAD, 
	///Charging error
	FAULT 
} BattState;
extern BattState GetBattState(void);
extern void SetBattState(BattState);
extern OSgltypeTick GetChargeTime(void); 

#define STR_TASK_BATT   "TaskBatt"
#endif
