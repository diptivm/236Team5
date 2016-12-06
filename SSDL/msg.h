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

#ifndef EOF_RETURN_CODE
#ifndef GETCHAR_PUTCHAR_RETURN_ZERO
#define  EOF_RETURN_CODE            EOF
#else
//#define  EOF_RETURN_CODE            0
#endif
#endif

#define CRLF                                "\n\r"
#define TICKS_BUFFER_SIZE                   30

#endif /* __MsgTS */

