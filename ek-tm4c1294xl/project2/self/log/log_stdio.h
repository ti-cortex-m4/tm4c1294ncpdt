/*------------------------------------------------------------------------------
log_stdio.h


------------------------------------------------------------------------------*/

#define LOG_BUFF_SIZE 1000



extern unsigned char mbLog[LOG_BUFF_SIZE];



void LogPrintF(const char *pcString, ...);
