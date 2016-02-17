/*------------------------------------------------------------------------------
uart_log.h


------------------------------------------------------------------------------*/

#include <stdint.h>
#include "utils/uartstdio.h"



void    LogTimer_1000Hz(void);

void    InitLog(void);
void    PrintLogTimer(void);



#ifdef DEBUG
#define LOG UARTprintf
#else
#define LOG
#endif
