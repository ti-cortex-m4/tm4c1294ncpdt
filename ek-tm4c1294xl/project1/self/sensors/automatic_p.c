/*------------------------------------------------------------------------------
AUTOMATIC_P.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../digitals/digitals.h"
#include "automatic1.h"
#include "device_p.h"
#include "automatic_p.h"



uchar                   ibMonthP;



#ifndef SKIP_P

void    QueryHistoryP1(uchar  ibRecord)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('4');
  PushChar('3');
  PushChar('0');
  PushChar(szDigits[ibRecord / 0x10]);
  PushChar(szDigits[ibRecord % 0x10]);
  PushChar('(');
  PushChar('0');
  PushChar('9');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+21+1, 4+11+1);
}


void    QueryHistoryP2(uchar  ibRecord)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('4');
  PushChar('3');
  PushChar('0');
  PushChar(szDigits[ibRecord / 0x10]);
  PushChar(szDigits[ibRecord % 0x10]);
  PushChar('(');
  PushChar('4');
  PushChar('0');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+131+1, 4+11+1);
}


void    QueryHistoryP3(uchar  ibRecord)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('D');
  PushChar(0x02);

  PushChar('5');
  PushChar('4');
  PushChar('3');
  PushChar('0');
  PushChar(szDigits[ibRecord / 0x10]);
  PushChar(szDigits[ibRecord % 0x10]);
  PushChar('(');
  PushChar('0');
  PushChar('1');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+261+1, 4+11+1);
}


time2   QueryTimeP_Full(void)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) == SER_GOODCHECK) break;  
    if (fKey == true) return GetTime2(tiZero, false);
  }

  if (i == bMINORREPEATS) return GetTime2(tiZero, false);

  time ti = ReadTimeP();
  ShowPercent(50);

  return GetTime2(ti, true);
}


bool    QueryHistoryP1_Full(uchar  ibRecord)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryHistoryP1(ibRecord*8+8);

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60+ibRecord);

  return(1);
}


bool    QueryHistoryP2_Full(uchar  ibRecord)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryHistoryP2(ibRecord);

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(80+ibRecord/8);

  return(1);
}


bool    QueryHistoryP3_Full(uchar  ibRecord)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryHistoryP3(ibRecord);

    if (ElsInputRD() != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60+ibRecord);

  return(1);
}


uint    PopChar2ElsHex(void)
{
  return (PopChar1Els()*0x10 + PopChar1Els());
}


double2 ReadCntMonCanP(uchar  ibMonth)
{
uchar   i,j;

  Clear();
  if (OpenDeviceP() == 0) return GetDouble2(0, false);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) == SER_GOODCHECK) break;
  }

  if (i == bMINORREPEATS) return GetDouble2(0, false);
  ShowPercent(50);

  time ti = ReadTimeP();


  if (ti.bMonth == ibMonth+1)
  {
    QueryCloseP();

    //sprintf(szLo, "  нет данных !  ");
    //Delay(1000); 
    return GetDouble2(0, false);
  }
  else
  {
    if (ReadKoeffDeviceP() == 0) return GetDouble2(0, false);

    tiDig.bYear = (ibMonth+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    tiDig.bMonth = ibMonth+1;

    tiDigPrev.bYear = tiDig.bYear;
    tiDigPrev.bMonth = tiDig.bMonth;

    if (++tiDig.bMonth > 12)
    {
      tiDig.bMonth = 1;
      tiDig.bYear++;
    }

    for (i=0; i<15; i++) 
    { 
      if (QueryHistoryP1_Full(i) == 0) return GetDouble2(0, false);

      InitPop(2+8);
      
      j = PopChar2ElsHex();

      combo32 co;
      co.mpbBuff[0] = PopChar2ElsHex();
      co.mpbBuff[1] = PopChar2ElsHex();
      co.mpbBuff[2] = PopChar2ElsHex();
      co.mpbBuff[3] = PopChar2ElsHex();

      ulong dwBuffC = co.dwBuff - (ulong)(23*365 + 7*366)*24*60*60;
      SecIndexToDate(dwBuffC);

      if ((j == 1) && (co.dwBuff != 0))
      {
        if ((tiDig.bMonth == ti.bMonth) && (tiDig.bYear == ti.bYear))
        {
          if (QueryHistoryP2_Full(i*8+1+0) == 0) return GetDouble2(0, false);
          ReadEngAbsP(0);
          if (QueryHistoryP2_Full(i*8+1+1) == 0) return GetDouble2(0, false);
          ReadEngAbsP(1);
       
          double dbTrans = mpdbTransCnt[ibDig];
          for (i=0; i<16; i++) 
          {
            mpdbChannelsC[i] *= dbTrans;
          }

          for (i=0; i<4; i++) 
          {
            if (mpbMappingEls[i] >= 16)
              mpdbChannelsEls[i] = 0;
            else
              mpdbChannelsEls[i] = mpdbChannelsC[mpbMappingEls[i]];
          }

          for (i=0; i<4; i++) 
          {
            mpdbChannelsC[i] = mpdbChannelsEls[i];
            mpboChannelsA[i] = true;
          }

          QueryCloseP();

          return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
        }
      }
    }
    
    QueryCloseP();

    sprintf(szLo, " мес€ц %02u.%02u ?  ",tiDigPrev.bMonth,tiDigPrev.bYear);
    Delay(1000); 
    return GetDouble2(0, false);
  }
}



void    ClrValueP(uchar  ibLine)
{
  mpreChannelsB[ibLine] = coEnergy.reBuff;
  mpboChannelsA[ibLine] = true;
}


void    SetValueP(uchar  ibLine, uchar  i)
{
  mpreChannelsB[ibLine] = mpreChannelsB[i];
  mpboChannelsA[ibLine] = true;
}


void    GetTariffP(uchar  ibTariff)
{
  coEnergy.mpbBuff[0] = 0xFF; 
  coEnergy.mpbBuff[1] = 0xFF; 
  coEnergy.mpbBuff[2] = 0xFF; 
  coEnergy.mpbBuff[3] = 0xFF; 

  if (ibTariff == 0)
  {
    SetValueP(0, 16);
    ClrValueP(1);
    SetValueP(2, 19);
    ClrValueP(3);
  }
  else if (ibTariff == 1)
  {
    SetValueP(0, 17);
    ClrValueP(1);
    SetValueP(2, 20);
    ClrValueP(3);
  }
  else if (ibTariff == 2)
  {
    SetValueP(0, 18);
    ClrValueP(1);
    SetValueP(2, 21);
    ClrValueP(3);
  }
  else
  {
    ClrValueP(0);
    ClrValueP(1);
    ClrValueP(2);
    ClrValueP(3);
  }
}



status  ReadCntMonCanTariffP(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{
uchar   i,j;

  if (ibMonth == ibMonthP)
  {
    GetTariffP(ibTariff);
    return(ST4_OK);
  }
  else
  {
    Clear();
    if (OpenDeviceP() == 0) return(ST4_BADDIGITAL);

    time2 ti2 = QueryTimeP_Full();
    if (ti2.fValid == false) return(ST4_BADDIGITAL);
    time ti = ti2.tiValue;

    if (ReadKoeffDeviceP() == 0) return(ST4_BADDIGITAL);

    tiDig.bYear  = (ibMonth+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    tiDig.bMonth = ibMonth+1;
    tiDig.bDay  = 1;

    for (i=0; i<15; i++) 
    {
      if (QueryHistoryP1_Full(i) == 0) return(ST4_BADDIGITAL);

      InitPop(2+8);
      
      j = PopChar2ElsHex();

      coTrue.mpbBuff[3] = PopChar2ElsHex();
      coTrue.mpbBuff[2] = PopChar2ElsHex();
      coTrue.mpbBuff[1] = PopChar2ElsHex();
      coTrue.mpbBuff[0] = PopChar2ElsHex();

      dwBuffC = coTrue.dwBuff - (ulong)(23*365 + 7*366)*24*60*60;
      SecIndexToDate(dwBuffC);
 
     if ((j == 1) && (coTrue.dwBuff != 0)) 
      {
        if ((tiDig.bMonth == ti.bMonth) && (tiDig.bYear == ti.bYear))
        { 
          if (QueryHistoryP3_Full(i*2+1) == 0) return(ST4_BADDIGITAL);
          ReadEngAbsP_RD();

          double dbTrans = mpdbTransCnt[ibDig];
          for (i=0; i<22; i++) 
          {
            mpdbChannelsC[i] *= dbTrans;
          }

          GetTariffP(ibTariff);

          QueryCloseP();
          return(ST4_OK);
        }
      }
    }
    
    QueryCloseP();

    sprintf(szLo, " мес€ц %02u.%02u ?  ",tiDig.bMonth,tiDig.bYear);
    Delay(1000);
    return(ST4_NOTPRESENTED);
  }
}


#endif
