/*------------------------------------------------------------------------------
printf,h


------------------------------------------------------------------------------*/

typedef struct
{
  unsigned char *pbBuff;
  unsigned int  wSize;
} buff_t;



buff_t LogPrintF(const char *pcString, ...);
void UdpPrintF(const char *pcString, ...);
