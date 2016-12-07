#include <salvo.h>
#include "config.h"
#include "msg.h"
#include "usart_uart.h"

/**

Function getDays()

Function that outputs the amount of days elapsed since the last reset, based on
the number of ticks obtained using OSGetTicks().

Input argument:  None
<br>Output argument:  Number of days elapsed 


*/

int getDays (void){
  int days;
  OSgltypeTick ticks;
  ticks = OSGetTicks();  
  ticks = ticks/100;
  days = ticks/86400;
  return (days);
}

/**

Function getHours()

Function that outputs the amount of hours elapsed since the last reset of the 
code, based on the number of ticks obtained using OSGetTicks(). The number of
hours rolls back to zero upon reaching 24 hours.

Input argument:  None
<br>Output argument:  Number of hours elapsed


*/

int getHours (void){
  unsigned long days;
  int hour;
  OSgltypeTick ticks;
  ticks = OSGetTicks();  
  ticks = ticks/100;
  days = ticks/86400;
  hour = (ticks - days*86400)/3600;
  return (hour);
}

/**

Function getMinutes()

Function that outputs the amount of minutes elapsed since the last reset of the
code, based on the number of ticks obtained using OSGetTicks(). The number of 
minutes rolls back to zero upon reaching 60 minutes.

Input argument:  None
<br>Output argument:  Number of minutes elapsed


*/

int getMinutes (void){
  unsigned long hours;
  int min;
  OSgltypeTick ticks;
  ticks = OSGetTicks();  
  ticks = ticks/100;
  hours = ticks/3600;
  min = (ticks - hours*3600)/60;
  return (min);
}

/**

Function getSeconds()

Function that outputs the amount of seconds elapsed since the last reset of the
code, based on the number of ticks obtained using OSGetTicks(). The number of 
seconds rolls back to zero upon reaching 60 seconds.

Input argument:  None
<br>Output argument:  Number of seconds elapsed


*/

int getSeconds (void){
  unsigned long min;
  int sec;
  OSgltypeTick ticks;
  ticks = OSGetTicks();  
  ticks = ticks/100;
  min = ticks/60;
  sec = ticks - min*60;
  return (sec);
}

/**

Function getTenMillis()

Function that outputs the amount of tens of milliseconds elapsed since the 
last reset of the code, based on the number of ticks obtained using OSGetTicks(). 
The number of tens of milliseconds rolls back to zero upon reaching 100.

Input argument:  None
<br>Output argument:  Number of tens of milliseconds elapsed  


*/

int getTenMillis(void) {
  unsigned long sec;
  int tenMillis;
  OSgltypeTick ticks;
  ticks = OSGetTicks();  
  sec = ticks/100;
  return tenMillis = ticks - sec*100;
}

/**

Function MsgTS()

Function that prints a time-stamped string, using the following format:
dd:hh:mm:ss.tt. The timing is based on the number of ticks measured by
OSGetTicks(), where each tick corresponds to 10 ms. The string can be dynamic 
using the % symbol and the appropriate variable. This function is implemented
whenever there is a need to directly display something on the terminal, 
as long as there is USB connection with the SSDL GPB/MSP430 board.

Input argument: String to be displayed
<br>Output argument: None


*/

void MsgTS (const char * cP) {

  unsigned int size;
  char strTicks[TICKS_BUFFER_SIZE];
  
  // Format strTicks to indicate which USART is talking, and display a timestamp.
  sprintf(strTicks, "1:%02i:%02i:%02i:%02i.%02i  ", getDays(), getHours(), getMinutes(), getSeconds(), getTenMillis());

  // Let's find out how big this string is ...
  size = 1 + sizeof(strTicks) + strlen(cP) + sizeof(CRLF);

  // Only if it can theoretically fit AND there's room in
  //  the buffer do we output it.
  if (size < TX1_BUFF_SIZE) {
    while (usart_uart1_tx_free() < size);
    usart_uart1_puts(strTicks);
    usart_uart1_puts(cP);
    usart_uart1_puts(CRLF);
  } /* if */
  
  // Else handle error.
}
 /* MsgTS() */