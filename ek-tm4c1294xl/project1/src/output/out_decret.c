/*------------------------------------------------------------------------------
OUT_DECRET.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"



void    OutDecret(void)
{
  InitPushCRC();
  PushChar(deDecret);
  Push(&tiSummer, sizeof(time));
  PushChar(cbSummer);
  Push(&tiWinter, sizeof(time));
  PushChar(cbWinter);
  Output(1+6+1+6+1);
}
