/*------------------------------------------------------------------------------
DEVICE_U.C

 Энергомера СЕ301
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../serial/ports_common.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
//#include "../digitals/digitals_messages.h"
#include "../digitals/limits.h"
//#include "../digitals/profile/refill.h"
//#include "../special/special.h"
//#include "../flash/records.h"
//#include "../energy.h"
//#include        "xdata.h"
//#include        "delay.h"
//#include        "display.h"
//#include        "engine.h"
//#include        "watchdog.h"
//#include        "timedate.h"
//#include        "ports.h"
//#include        "limits.h"
//#include        "digitals.h"
#include "device_k.h"
#include "device_q.h"
//#include        "essential.h"
//#include        "_timedate.h"



#ifndef SKIP_U

void    QueryCloseU(void)
{
  QueryCloseK();
}



void    QueryOptionU(void)
{
uchar   i;

  InitPush(0);
  PushChar1Bcc(0x06);

  switch (mppoPorts[ diCurr.ibPort ].ibSpeed)
  {
    case 0:  i = '2'; break;
    case 1:  i = '3'; break;
    case 2:  i = '4'; break;
    case 3:  i = '5'; break;
    case 4:  i = '6'; break;
    default: i = '7'; break;
  }

  PushChar1Bcc('0');
  PushChar1Bcc(i);
  PushChar1Bcc('1');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  cbHeaderBcc = 1;
  cwInBuffBcc = 0;
  Query(1000, 4+2, 1);
}


void    QueryCorrectU(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('!');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(1000, 2+6+2, 1);
}


void    QueryEnergyAbsU(uchar  ibLine)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+8+1, 6);
}


void    QueryEnergyDayU(uchar  ibLine)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('D');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(tiAlt.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+16+1, 6);
}


void    QueryEnergyMonU(uchar  ibLine)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('M');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(tiAlt.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+13+1, 6);
}


void    QueryEnergySpecU(uchar  ibLine)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+6*28+2, 4+8+1, 6);
}


void    ReadEnergyU(uchar  ibLine)
{
  InitPop(1);

  PopRealQ();
  mpreChannelsB[ibLine] = reBuffA;
}


void    ReadEnergyU_SkipLine(uchar  ibLine)
{
  mpreChannelsB[ibLine] = 0;
}


void    InitHeaderU(void)
{
  if (!UseBounds())
    wBaseCurr = 0;  // счетчик суток
  else 
  {
    wBaseCurr = mpcwStartAbsCan[ibDig];
    sprintf(szLo,"   начало %2bu    ",wBaseCurr);
    DelayMsg();
  }
      
  tiDigPrev = tiCurr;   
}


void    QueryHeaderU_26(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');
  PushChar1Bcc('P');
  PushChar1Bcc((ibMinor == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO1(2000, 4+16+1, 48);
}


void    QueryHeaderU(void)
{
  NoShowTime(1);

  if (wBaseCurr == 0) 
    tiDig = tiDigPrev;
  else
  {
    tiAlt = tiDigPrev;
    dwBuffC = DateToDayIndex();
       
    dwBuffC -= wBaseCurr;   
     
    DayIndexToDate(dwBuffC);
    tiDig = tiAlt;
    tiDig.bHour   = 23;
    tiDig.bMinute = 30;
  }           
         
  szHi[10] = 'A' + ibMinor;       
     
  ibMinorMax = 2;
  QueryHeaderU_26();
}



void    ReadHeaderU(void)
{
uchar   j;

  InitPop(1);

  for (j=0; j<48; j++)
  {
    PopRealQ();
    mpreBuffCanHou[ibMinor][j] = reBuffA/2;
  }
}


void    ReadHeaderU_SkipLine(uchar  ibLine)
{
uchar   j;

  for (j=0; j<48; j++)
    mpreBuffCanHou[ibLine][j] = 0;
}



void    MakeDataU(uchar  ibHou)
{
  ShowProgressDigHou();      
  reBuffB = mpdbPulseHou[ibDig];

  for (ibCan=0; ibCan<ibMinorMax; ibCan++)        
  {
    reBuffA = mpreBuffCanHou[ibCan][ibHou];   
    mpreEngFracDigCan[ibDig][ibCan] += reBuffA;

    wBuffD = (uint)(mpreEngFracDigCan[ibDig][ibCan]*reBuffB);
    mpwChannels[ibCan] = wBuffD;

    mpreEngFracDigCan[ibDig][ibCan] -= (float)wBuffD/reBuffB;
  }
}


bool    ReadDataU(void)
{
uchar   i,j;
       
  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем время/дату часового блока
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
       
  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(1);             
       
  if ((tiDig.bDay   == tiCurr.bDay)   &&
      (tiDig.bMonth == tiCurr.bMonth) &&
      (tiDig.bYear  == tiCurr.bYear))
    j = 47-(tiCurr.bHour*2+tiCurr.bMinute/30);
  else
    j = 0;
      
  tiAlt = tiDig;
  dwHouIndex = DateToHouIndex();

  for (i=j; i<48; i++) 
  {           
    ResetWDT();
    MakeDataU(47-i);
      
    tiAlt = tiDig;
    MakePrevHou();
    if (MakeStopHou(0) == 0) return(0);
                
    dwHouIndex--;
       
    HouIndexToDate(dwHouIndex);
    tiDig = tiAlt;
      
    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;      
  }
       
  NewBoundsAbs(++wBaseCurr);
  return(1);
}



void    ReadCurrentU(void)
{
uchar   i;

  reBuffB = mpdbPulseHou[ibDig];

  for (i=0; i<2; i++)
  {
    dwBuffC = mpreChannelsB[i] * reBuffB;
    mpdwBaseDig[i] = dwBuffC;
  }

  MakeCurrent();
}



void    QueryParamU1(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('C');
  PushChar1Bcc('U');
  PushChar1Bcc('R');
  PushChar1Bcc('R');
  PushChar1Bcc('E');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU2(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('V');
  PushChar1Bcc('O');
  PushChar1Bcc('L');
  PushChar1Bcc('T');
  PushChar1Bcc('A');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU3(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('P');
  PushChar1Bcc('P');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU4(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('F');
  PushChar1Bcc('R');
  PushChar1Bcc('E');
  PushChar1Bcc('Q');
  PushChar1Bcc('U');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+1*28+2, 15+8+1, 1);
}

#endif
