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

void    UnpackW(bool  fShow)
{
uint    i;
uchar   j;

  if (cbHeaderBcc == 0) return;

  if (cwInBuffBcc == IndexInBuff()) return;
  cwInBuffBcc = IndexInBuff();

  if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

  if (IndexInBuff() > 2)
  {
    InitPop(1);

    j = 0;
    for (i=0; i<IndexInBuff()-2; i++)
    {
      if (PopChar0Bcc() == ')') j++;

      if ((j == cbHeaderBcc) && (i+6 == IndexInBuff()))
      {
        SetCountInBuff(i+6);

        if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

        MonitorIn();

        InputMode();
        mpSerial[ibPort] = SER_POSTINPUT_MASTER;
        break;
      }
    }
  }
}


void    UnpackW2(bool  fShow, uchar  bOffset)
{
uint    i;
uchar   j;

  if (cbHeaderBcc == 0) return;

  if (cwInBuffBcc == IndexInBuff()) return;
  cwInBuffBcc = IndexInBuff();

  if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

  if (IndexInBuff() > 2)
  {
    InitPop(1);

    j = 0;
    for (i=0; i<IndexInBuff()-2; i++)
    {
      if (PopChar0Bcc() == ')') j++;

      if ((j == cbHeaderBcc) && (i+bOffset == IndexInBuff()))
      {
        SetCountInBuff(i+bOffset);

        if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

        MonitorIn();

        InputMode();
        mpSerial[ibPort] = SER_POSTINPUT_MASTER;
        break;
      }
    }
  }
}

#endif
