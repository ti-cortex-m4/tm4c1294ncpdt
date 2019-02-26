/*------------------------------------------------------------------------------
DEVICE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../hardware/beep.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "unix_time_gmt34.h"
#include "energy34.h"
#include "device34.h"



void    ShowFoundNumber(uchar  i);



#ifndef SKIP_34

float   PopFloat34(void)
{
  static combo32 co;

  co.mpbBuff[0] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[3] = PopChar();

  return co.flBuff;
}



bool    ChangeNumber34(uchar  bNumber)
{
  InitPush(0);

  PushChar(bNumber);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}


bool    ChangeSpeed34(void)
{
  InitPush(0);

  PushChar(0);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  ShowFoundNumber(InBuff(0));
  return(1);
}



void    QueryConfig34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6C);

  QueryIO(3+32+2, 2+2);
}



void    QueryEngAbs34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(3+81+2, 8+2);
}


void    ReadEng34(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpddwChannels34[i] = PopLongLtl();
    mpddwChannels34[i] += 0x100000000*PopLongLtl();
  }
}



void    ReadCurrent34(void)
{
  ReadEng34();

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdwBaseDig[i] = mpddwChannels34[i] / 100;
  }

  MakeCurrent();
}

#endif

