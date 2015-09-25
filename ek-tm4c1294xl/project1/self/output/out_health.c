/*------------------------------------------------------------------------------
OUT_HEALTH!C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../health.h"



void    OutHealth(void)
{
uint    i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(UNDEFINED);

  InitPushCRC();
  PushBool(fHealthLabelRTC);
  PushBool(fHealthTimeRTC);

  Output(1000);
}
