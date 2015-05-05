/*------------------------------------------------------------------------------
OUT_DECRET,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"



void    OutDecret(void)
{
  InitPushCRC();

  PushChar(deDecret);

  PushTime(tiSummer);
  PushChar(cbSummer);

  PushTime(tiWinter);
  PushChar(cbWinter);

  Output(1+6+1+6+1);
}
