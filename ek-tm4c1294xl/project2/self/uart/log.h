/*------------------------------------------------------------------------------
LOG.H


------------------------------------------------------------------------------*/

void    LogTimer_1000Hz(void);

void    InitLog(void);
void    PrintLogTimer(void);



#ifdef DEBUG
#define LOG(msg) { UARTprintf (msg); }
#else
#define LOG(msg)
#endif
