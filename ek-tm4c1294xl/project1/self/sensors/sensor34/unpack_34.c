/*------------------------------------------------------------------------------
UNPACK_34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../kernel/crc-16.h"
#include "device34.h"
#include "unpack_34.h"



#ifndef SKIP_34

void    UnpackCorrect34(void)
{
  if (IndexInBuff() == 5)
  {
    MakeCRC16InBuff(0, IndexInBuff());
    if ((bCRCHi == 0) && (bCRCLo == 0))
    {
#if MONITOR_34
      MonitorString("\n unpack: time correct");
#endif
      SetCountInBuff(IndexInBuff());
      mpSerial[ibPort] = SER_POSTINPUT_MASTER;
    }
  }
}


void    UnpackProfile34(void)
{
  if (IndexInBuff() > 6)
  {
    uint wSize = InBuff(4) + 0x100*InBuff(5);
    if (IndexInBuff() == 4+2+2+wSize*24+2)
    {
      SetCountInBuff(IndexInBuff());
      mpSerial[ibPort] = SER_POSTINPUT_MASTER;
    }
  }
}

#endif
