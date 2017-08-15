/*------------------------------------------------------------------------------
OUT_ECHO!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutEchoNtoN(void)
{
  if (CountInBuff() < 8)
    Result(bRES_BADDATA);
  else
  {
    const uint wSize = CountInBuff() - 7;

    if (wSize >= (wOUTBUFF_SIZE-0x40))
      Result(bRES_OUTOVERFLOW);
    else
    {
      InitPushCRC();

      uint i;
      for (i=0; i<wSize; i++)
        PushChar(InBuff(i + 5));

      Output(wSize);
    }
  }
}


void    OutEchoNto1(void)
{
  InitPushCRC();
  PushIntBig(CountInBuff());
  Output(2);
}


void    OutEcho1toN(void)
{
  const uchar b = bInBuff6;
  const uint wSize = bInBuff7*0x100 + bInBuff8;

  if (wSize >= (wOUTBUFF_SIZE-0x40))
    Result(bRES_OUTOVERFLOW);
  else
  {
    InitPushCRC();

    uint i;
    for (i=0; i<wSize; i++)
      PushChar(b);

    Output(wSize);
  }
}
