/*------------------------------------------------------------------------------
OUT_HEALTH!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutHealth(void)
{
uint    i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0x55);

  InitPushCRC();
  PushBool(fHealthLabelRTC);
  PushBool(fHealthTimeRTC);

  Output(1000);
}
