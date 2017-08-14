/*------------------------------------------------------------------------------
OUT_ECHO!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutEcho(void)
{
  uint wSize = bInBuff6*0x100 + bInBuff7;

  if (wSize >= (wOUTBUFF_SIZE-0x40))
    Result(bRES_OUTOVERFLOW);
  else
  {
    InitPushCRC();

    uint i;
    for (i=0; i<wSize; i++)
      PushChar(0x55);

    Output(wSize);
  }
}
