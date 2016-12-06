/**
/******************************************************************************
****                                                                       ****
**                                                                           **
Functions available to all who include msg.h.

**                                                                           **
****                                                                       ****
*******************************************************************************
*/
extern int getDays(void);
extern int getHours(void);
extern int getMinutes(void);
extern int getSeconds(void);
extern int getTenMillis(void);
extern void MsgTS(const char * cP);

#ifndef __MsgTS
#define __MsgTS

#define CRLF                                "\n\r"
#define TICKS_BUFFER_SIZE                   30

#endif /* __MsgTS */


