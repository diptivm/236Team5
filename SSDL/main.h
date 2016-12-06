#ifndef __main_h
#define __main_h

/**
/******************************************************************************
****                                                                       ****
**                                                                           **
Project-wide definitions and other items that might be used across a multitude
of files ... kind of a catch-all.

**                                                                           **
****                                                                       ****
*******************************************************************************
*/

extern char strTmp[];            // Anyone can use this shared buffer

#define VERSION_NUM                     "0.0.1"

#define TIMERA0_RELOAD                  328

#define LOOP_HERE()                     do { ; } while (1) 
#define NOP		                _NOP()

// control of Watchdog timer
#define WDT_OFF				WDTCTL = WDTPW + WDTHOLD
#define WDT_ON				WDTCTL = WDT_ARST_250

#define SEM_UI_CHAR                     OSECBP(1)

// Application-wide constants (battery states)
#define VBATT_NEARLY_DEAD               2.90
#define VBATT_PARTIALLY_CHARGED         3.60
#define VBATT_FULLY_CHARGED             4.13

#endif /* __main_h */
