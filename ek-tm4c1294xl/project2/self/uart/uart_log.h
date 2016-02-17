/*------------------------------------------------------------------------------
uart_log.h


------------------------------------------------------------------------------*/

void    LogTimer_1000Hz(void);

void    InitUartLog(ulong dwSysClockFreq);
void    PrintLogTimer(void);



#ifdef DEBUG
#define LOG UARTprintf
#else
#define LOG
#endif
