/*------------------------------------------------------------------------------
printf.h


------------------------------------------------------------------------------*/

typedef struct
{
  void         *pbBuff;
  uint          wSize;
} buff;



void UDPPrintF(const char *pcsz, ...);
void DebugPrintF(const char *pcsz, ...);
buff BuffPrintF(const char *pcsz, ...);
