/*------------------------------------------------------------------------------
current38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../serial/ports.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
//#include "../../digitals/current/current_run.h"
//#include "io36.h"
//#include "../device_k.h"
#include "current38.h"


/*
uchar   GetMaxLine36(uchar  ibCan)
{
  switch (GetDigitalDevice(ibCan))
  {
    case 36: return 2;
    case 37: return 4;
    default: ASSERT(false); return 0;
  }
}


void    QueryEngCurrent36(uchar  ibLine)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+6*28+2, 4+8+1, 6);
}


void    ReadCurrent36(uchar  bMaxLine)
{
  uchar i;
  for (i=0; i<bMaxLine; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}
*/
