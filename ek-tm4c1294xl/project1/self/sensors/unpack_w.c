/*------------------------------------------------------------------------------
UNPACK_W!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../serial/monitor.h"
#include "../display/display.h"
#include "unpack_w.h"



#ifndef SKIP_W

void    UnpackW(bool  fShow, uchar  bOffset)
{
  if (cbHeaderBcc == 0) return;

  if (cwInBuffBcc == IndexInBuff()) return;
  cwInBuffBcc = IndexInBuff();

  if ((fShow == true) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

  if (IndexInBuff() > 2)
  {
    InitPop(1);

    uint j = 0;

    uchar i;
    for (i=0; i<IndexInBuff()-2; i++)
    {
      if (PopChar0Bcc() == ')') j++;

      if ((j == cbHeaderBcc) && (i+bOffset == IndexInBuff()))
      {
        SetCountInBuff(i+bOffset+1);

        if ((fShow == true) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

        MonitorIn();

        InputMode();
        mpSerial[ibPort] = SER_POSTINPUT_MASTER;
        break;
      }
    }
  }
}

#endif
