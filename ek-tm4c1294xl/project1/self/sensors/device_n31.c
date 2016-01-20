/*------------------------------------------------------------------------------
DEVICE_N31.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
//#include "../memory/mem_current.h"
//#include "../memory/mem_factors.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy_spec.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_limits.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
//#include "../serial/monitor.h"
#include "../display/display.h"
//#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
#include "../time/delay.h"
//#include "../devices/devices.h"
//#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
//#include "../digitals/limits.h"
#include "../digitals/digitals_messages.h"
//#include "../special/special.h"
#include "automatic_n31.h"
//#include "device_k.h"
#include "device_n31.h"



#ifndef SKIP_N31

uchar                   bVersionN31;



bool    ExtVersionN31()
{
  return ((bVersionN31 == 36) ||
          (bVersionN31 == 37) ||
          (bVersionN31 == 49));
}



void    QueryCloseN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  QueryN31(0, 3+1);
}


void    QueryOpenN31(void)
{
  QueryCloseN31();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  QueryN31(3+8+1, 3+8+1);
}


bool    ReadOpenN31(void)
{
  InitPop(3);

  bVersionN31 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"версия: %2u",bVersionN31);
  DelayInf(); Clear();

  if ((bVersionN31 == 22) ||
      (bVersionN31 == 33) ||
      (bVersionN31 == 35) ||
      (bVersionN31 == 36) ||
      (bVersionN31 == 37) ||
      (bVersionN31 == 49)) return(1);

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}



void    QueryTimeN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  QueryN31(3+8+1, 3+1);
}


time    ReadTimeN31(void)
{
  time ti;

  InitPop(3);
               PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();

  uint y;
  if (ExtVersionN31())
    y = PopIntLtl();
  else
    y = PopIntBig();

  ti.bYear   = y % 100;

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}



void    QueryEngAbsN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x12);

  if (ExtVersionN31())
    QueryN31(3+48+1, 3+1);
  else
    QueryN31(3+42+1, 3+1);
}



void    PopRealBCD_G(void)
{
//uchar   i,j;
//
//  reBuffA = 0;
//
//  for (i=0; i<6; i++) reBuffA = reBuffA*100 + FromBCD( PopChar() );
//  for (i=0; i<6; i++) reBuffA /= 100;
//
//  i = PopChar();
//  j = i & 0x3F;
//
//  if ((i & 0x40) == 0)
//    while (j-- > 0) reBuffA /= 10;
//  else
//    while (j-- > 0) reBuffA *= 10;
//
//  if ((i & 0x80) != 0) reBuffA *= -1;
}


void    PopRealExt_G(void)
{
//uchar   a,b,c;
//uint    x;
//
//  PopChar();
//  PopChar();
//  PopChar();
//
//  coFloat.mpbBuff[3] = PopChar();
//  coFloat.mpbBuff[2] = PopChar();
//  coFloat.mpbBuff[1] = PopChar();
//  a = PopChar();
//  b = PopChar();
//
//  coFloat.mpbBuff[0] = a  & 0x0F;
//  coFloat.dwBuff <<= 3;
//
//  x = (b & 0x7F)*0x100 + (a & 0xF0);
//  x >>= 4;
//  c = x - 896;
//
//  coFloat.mpbBuff[3] = coFloat.mpbBuff[2];
//  coFloat.mpbBuff[2] = coFloat.mpbBuff[1];
//  coFloat.mpbBuff[1] = coFloat.mpbBuff[0];
//  coFloat.mpbBuff[0] = c >> 1;
//
//  if ((c & 0x01) != 0) coFloat.mpbBuff[1] |= 0x80;
//  if ((b & 0x80) != 0) coFloat.mpbBuff[0] |= 0x80;
//
//  reBuffA = coFloat.reBuff;
}


void    ReadEngN31(void)
{
  InitPop(3);

//  uchar i;
//  for (i=0; i<6; i++)
//  {
//    if (ExtVersionCod())
//      PopRealExt_G();
//    else
//      PopRealBCD_G();
//
//    reBuffA /= 1000;
//
//    SetCanReal(mpreChannelsB, i);
//    mpboChannelsA[i] = boTrue;
//  }
//
//  reBuffA = *PGetCanReal(&mpreChannelsB, diCurr.ibLine);
}


#endif
