/*------------------------------------------------------------------------------
log_stdio.h


------------------------------------------------------------------------------*/

typedef struct
{
  unsigned char *pbData;
  unsigned int  wSize;
} log_t;



log_t LogPrintF(const char *pcString, ...);
