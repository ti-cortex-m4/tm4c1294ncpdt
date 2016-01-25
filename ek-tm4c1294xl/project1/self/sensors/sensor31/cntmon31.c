/*------------------------------------------------------------------------------
CNTMON31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "automatic31.h"
#include "device31.h"
#include "cntmon31.h"



#ifndef SKIP_N31

// промежуточные буфера
static double           mpreChannelsMonG[6],
                        mpreChannelsAbsG[6];

// промежуточные буфера
static uchar            mpbChannelsMonG[13];

// массив потреблённой энергии
static double           mpreCodEng30[30];



void    QueryIndex4_G(uchar  ibTrf)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04);
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  QueryN31(3+4+8*24+2+1, 3+3+1);
}


void    QueryIndex5_G(uchar  ibTrf)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x05);
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  QueryN31(3+4+8*6+2+1, 3+3+1);
}


void    QueryIndex26_G(uchar  ibMon, uchar  ibTrf)
{
uint  i;

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  i = ibMon * 72 + ibTrf;
  PushCharCod(26);
  PushCharCod(i / 0x100);
  PushCharCod(i % 0x100);

  QueryN31(3+102+1, 3+3+1);
}



static bool ValidPackTime(void)
{
  time ti = ReadPackTimeN31();

  if ((ti.bSecond == 0) &&
      (ti.bMinute == 0) &&
      (ti.bHour   == 0) &&
      (ti.bDay    == 0) &&
      (ti.bMonth  == 0) &&
      (ti.bYear   == 0)) return false;

  return true;
}


bool    ReadEnergyExt_G(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счётчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex5_G(t);

      ShowPercent(60+t);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break;         // тариф не используется
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 52);
        if (wCRC != InBuff(55) + InBuff(56)*0x100) { sprintf(szLo," ошибка CRC: G0 "); Delay(1000); return(0); }

        for (r=0; r<6; r++)
        {
          mpreCodEng30[r*5] += PopDoubleN31()/1000;
        }
      }
    }
  }

  for (t=0; t<bTARIFFS; t++) // в счётчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex4_G(t);

      ShowPercent(70+t);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // тариф не используется
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 196);
        if (wCRC != InBuff(199) + InBuff(200)*0x100) { sprintf(szLo," ошибка CRC: G1 "); Delay(1000); return(0); }

        for (r=0; r<24; r++)
        {
          mpreCodEng30[1 + (r/4)*5 + r%4] += PopDoubleN31()/1000;
        }
      }
    }
  }

  return(1);
}


bool    ReadMonthIndexExt_G(void)
{
  uchar m;
  for (m=0; m<=12; m++)
  {
    if (fKey == true) return(0);

    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex26_G(m, 0);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return 0xEE;
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { sprintf(szLo," ошибка CRC: G2 "); Delay(1000); return(0); }

      time ti = ReadPackTimeN31();

      if (ti.bMonth == 0)
        mpbChannelsMonG[m] = 0;
      else
        mpbChannelsMonG[m] = (10 + ti.bMonth)%12 + 1;

      if (ti.bMonth != 0)
        { sprintf(szLo,"  найдено: %-2u   ", mpbChannelsMonG[m]); Delay(200); }
      else
        sprintf(szLo," пусто: %2u-%-2u   ",m,12);
    }
  }

  return(1);
}


uchar   SearchMonthIndexExt_G(uchar  bMonth)
{
uchar i;

  sprintf(szLo," требуется: %-2u  ", bMonth); DelayInf();

  for (i=0; i<=12; i++)
    if (mpbChannelsMonG[i] == bMonth)
      return i;

  return 0xFF;
}


bool  ReadEngMonExt_G(uchar  ibMonth)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счётчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex26_G(ibMonth, t);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { sprintf(szLo," ошибка CRC: G3 "); Delay(1000); return(0); }

      InitPop(7); // !

      uchar i;
      for (i=0; i<6; i++)
      {
        mpreChannelsMonG[i] += PopDoubleN31()/1000;
      }
    }
  }

  return(1);
}


bool  ReadEngMonCurrExt_G(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счётчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex4_G(t);

      ShowPercent(80+t);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // тариф не используется
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 196);
        if (wCRC != InBuff(199) + InBuff(200)*0x100) { sprintf(szLo," ошибка CRC: G4 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<24; i++)
        {
          mpreCodEng30[1 + (i/4)*5 + i%4] += PopDoubleN31()/1000;
        }
      }
    }
  }

  uchar i;
  for (i=0; i<6; i++)
  {
    mpreChannelsMonG[i] += mpreCodEng30[i*5+1];
  }

  return(1);
}


bool    ReadEngAbsExt_G(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счётчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryIndex5_G(t);

      ShowPercent(90+t);

      if (InputN31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // тариф не используется
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 52);
        if (wCRC != InBuff(55) + InBuff(56)*0x100) { sprintf(szLo," ошибка CRC: G5 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<6; i++)
        {
          mpreChannelsAbsG[i] += PopDoubleN31()/1000;
        }
      }
    }
  }

  return(1);
}


double2 ReadCntMonCanExt_G(uchar  ibMonth, time  tiAlt)
{
  if (ReadMonthIndexExt_G() == 0) return GetDouble2Error();
  Clear();


  uchar i;
  for (i=0; i<6; i++) mpreChannelsMonG[i] = 0;

  uchar m = ibMonth+1;
  uchar ibDay = 0;
  do
  {
    if ((m%12 + 1) == tiAlt.bMonth)
    {
      if (ReadEngMonCurrExt_G() == 0) return GetDouble2Error();
    }
    else
    {
      uchar ibGrp = SearchMonthIndexExt_G(m%12 + 1);
      if (ibGrp == 0xFF) { sprintf(szLo,"  отсутствует ! "); Delay(1000); return GetDouble2Error(); }
      Clear();
      if (ReadEngMonExt_G(ibGrp) == 0) return GetDouble2Error();
    }
    ShowPercent(80 + ibDay++);
  }
  while ((bMONTHS + tiAlt.bMonth - ++m) % bMONTHS != 0 );


  for (i=0; i<6; i++) mpreChannelsAbsG[i] = 0;

  if (ReadEngAbsExt_G() == 0) return GetDouble2Error();
  ShowPercent(99);


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpreChannelsAbsG[i] - mpreChannelsMonG[i];
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan31(uchar  ibMon)
{
  time2 ti2 = QueryTimeN31_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;


  uchar i;
  for (i=0; i<30; i++) mpreCodEng30[i] = 0;

  if (ExtVersion31())
  {
    if (ti.bMonth != ibMon+1)
    {
      if (GetVersion31() == 49)
        return ReadCntMonCanExt_G(ibMon, tiX);
      else
        { sprintf(szLo,"   необходима   "); Delay(1000); sprintf(szLo,"   версия 49    "); Delay(1000); return GetDouble2Error(); }
    }
    else // значенияе счётчиков на начало текущего месяца
    {
      if (ReadEnergyExt_G() == 0) return GetDouble2Error();
    }
  }
  else
  {
    ShowLo(szNoVersion); Delay(1000); return GetDouble2Error();
  }

  ShowPercent(100);


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpreCodEng30[i*5+0] - mpreCodEng30[i*5+3];
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif
