/************************************************************
Copyright (C) 1995-2007 Pumpkin, Inc. and its
Licensor(s).

This file may be distributed under the terms of the License
Agreement provided with this software.

THIS FILE IS PROVIDED AS IS WITH NO WARRANTY OF ANY KIND,
INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE.

$Source: C:\\RCS\\D\\Pumpkin\\Library\\MSP430\\Inc\\USART_UART_msg_ts.h,v $
$Author: aek $
$Revision: 3.2 $
$Date: 2009-11-01 22:53:24-08 $

************************************************************/

#ifndef __MsgTS
#define __MsgTS


#ifndef GETCHAR_PUTCHAR_RETURN_ZERO
#define  EOF_RETURN_CODE            EOF
#else
//#define  EOF_RETURN_CODE            0
#endif

#define CRLF                                "\n\r"
#define TICKS_BUFFER_SIZE                   30

extern int getDays(void);
extern int getHours(void);
extern int getMinutes(void);
extern int getSeconds(void);
extern int getTenMillis(void);
extern void MsgTS(const char * cP);


#endif /* __MsgTS */


