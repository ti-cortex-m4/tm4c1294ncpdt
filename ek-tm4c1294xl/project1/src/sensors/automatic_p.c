/*------------------------------------------------------------------------------
AUTOMATIC_P.C


------------------------------------------------------------------------------*/

#include "../main.h"
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


bit     QueryTimeP_Full(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadTimeAltP();
  ShowPercent(50);

  return(1);
}


bit     QueryHistoryP1_Full(uchar  ibRecord)
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


bit     QueryHistoryP2_Full(uchar  ibRecord)
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


bit     QueryHistoryP3_Full(uchar  ibRecord)
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


bit     ReadCntMonCanP(uchar  ibMonth)
{
uchar   i,j;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadTimeAltP();


  if (tiAlt.bMonth == ibMonth+1)
  {
    QueryCloseP();

    //sprintf(szLo, "  нет данных !  ");
    //Delay(1000); 
    return(0);
  }
  else
  {
    if (ReadKoeffDeviceP() == 0) return(0);

    tiDig.bYear = (ibMonth+1 > tiAlt.bMonth) ? tiAlt.bYear-1 : tiAlt.bYear;
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
      if (QueryHistoryP1_Full(i) == 0) return(0);

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
        if ((tiDig.bMonth == tiAlt.bMonth) && (tiDig.bYear == tiAlt.bYear))
        {
          if (QueryHistoryP2_Full(i*8+1+0) == 0) return(0);
          ReadEngAbsP(0);
          if (QueryHistoryP2_Full(i*8+1+1) == 0) return(0);
          ReadEngAbsP(1);
       
          reBuffB = mpreTransCnt[ibDig];
          for (i=0; i<16; i++) 
          {
            mpreChannelsB[i] *= reBuffB;
          }

          for (i=0; i<4; i++) 
          {
            if (mpbMappingEls[i] >= 16)
              mpreChannelsEls[i] = 0;
            else
              mpreChannelsEls[i] = mpreChannelsB[mpbMappingEls[i]];
          }

          for (i=0; i<4; i++) 
          {
            mpreChannelsB[i] = mpreChannelsEls[i];
            mpboChannelsA[i] = TRUE;
          }

          QueryCloseP();

          reBuffA = mpreChannelsB[diCurr.ibLine];
          return(1);
        }
      }
    }
    
    QueryCloseP();

    sprintf(szLo, " мес€ц %02bu.%02bu ?  ",tiDigPrev.bMonth,tiDigPrev.bYear);
    Delay(1000); 
    return(0);
  }
}



void    ClrValueP(uchar  ibLine)
{
  mpreChannelsB[ibLine] = coEnergy.reBuff;
  mpboChannelsA[ibLine] = TRUE;
}


void    SetValueP(uchar  ibLine, uchar  i)
{
  mpreChannelsB[ibLine] = mpreChannelsB[i];
  mpboChannelsA[ibLine] = TRUE;
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



status4 ReadCntMonCanTariffP(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
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

    if (QueryTimeP_Full() == 0) return(ST4_BADDIGITAL);

    if (ReadKoeffDeviceP() == 0) return(ST4_BADDIGITAL);

    tiDig.bYear  = (ibMonth+1 > tiAlt.bMonth) ? tiAlt.bYear-1 : tiAlt.bYear;
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
        if ((tiDig.bMonth == tiAlt.bMonth) && (tiDig.bYear == tiAlt.bYear))
        { 
          if (QueryHistoryP3_Full(i*2+1) == 0) return(ST4_BADDIGITAL);
          ReadEngAbsP_RD();

          reBuffB = mpreTransCnt[ibDig];
          for (i=0; i<22; i++) 
          {
            mpreChannelsB[i] *= reBuffB;
          }

          GetTariffP(ibTariff);

          QueryCloseP();
          return(ST4_OK);
        }
      }
    }
    
    QueryCloseP();

    sprintf(szLo, " мес€ц %02bu.%02bu ?  ",tiDig.bMonth,tiDig.bYear);
    Delay(1000);
    return(ST4_NOTPRESENTED);
  }
}


#endif
