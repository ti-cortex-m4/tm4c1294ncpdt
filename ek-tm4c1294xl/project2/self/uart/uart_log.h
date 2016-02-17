/*------------------------------------------------------------------------------
uart_log.h


------------------------------------------------------------------------------*/

#include "uart_printf.h"



//void    LogTimer_1000Hz(void);

void    InitUartLog(ulong dwSysClockFreq);
//void    PrintLogTimer(void);



#ifdef DEBUG
#define LOG UartPrintF
#else
#define LOG
#endif
