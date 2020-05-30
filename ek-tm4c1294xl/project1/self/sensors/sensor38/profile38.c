/*------------------------------------------------------------------------------
profile38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "profile38.h"



void    QueryProfile38(uchar  ib30MinRel)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0xD5); // 213
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD6); // 214
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD7); // 215
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD8); // 216
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  Query38(250, 29);
}


bool    ReadHeader38(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 5;
    dw -= (wProfileC + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValueC)
      if (ReadHeaderC(5-i) == 0) return(0);
  }

  wProfileC += 6;
  if (wProfileC > wHOURS) return(0);

  MonitorString("\n");
  return(1);
}

//  (wBaseCurr > wHOURS/48)
