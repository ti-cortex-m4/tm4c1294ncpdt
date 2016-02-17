/*------------------------------------------------------------------------------
uart_log.h


------------------------------------------------------------------------------*/

#include "utils/uartstdio.h"
#include "uart_printf.h"



//void    LogTimer_1000Hz(void);

void    InitUartLog(ulong dwSysClockFreq);
//void    PrintLogTimer(void);



#ifdef DEBUG
#define CONSOLE_UART UartPrintF
#define ERROR_UART UARTprintf
#else
#define CONSOLE_UART
#define ERROR_UART
#endif
