/*------------------------------------------------------------------------------
LOG.H


------------------------------------------------------------------------------*/

void    LogTimer_1000Hz(void);
void    PrintLogTimer(void);



//#define USE_LOG



#ifdef USE_LOG
#define LOG(msg) PrintLogTimer(); UARTprintf msg
#else
#define LOG(msg)
#endif
