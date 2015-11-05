/*------------------------------------------------------------------------------
LOG.H


------------------------------------------------------------------------------*/

void    IncLogTimer(void);
void    OutLogTimer(void);



#define USE_LOG

#ifdef USE_LOG
#define LOG(msg) OutLogTimer(); UARTprintf msg
#else
#define LOG(msg)
#endif
