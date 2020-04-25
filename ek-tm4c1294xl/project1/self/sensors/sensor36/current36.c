/*------------------------------------------------------------------------------
current36,C

Энергомера СЕ301 NNCL2, СЕ303 NNCL2
------------------------------------------------------------------------------*/

#include "../../main.h"
////#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
////#include "../../display/display.h"
////#include "../../time/timedate.h"
////#include "../../time/calendar.h"
////#include "../../time/delay.h"
#include "../../serial/ports.h"
////#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "io36.h"
//#include "timeout35.h"
//#include "../device_k.h"
//#include "../device_q.h"
#include "current36.h"



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

  Query36(1+6*28+2, 4+8+1, 6);
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
