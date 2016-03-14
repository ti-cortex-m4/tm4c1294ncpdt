/*------------------------------------------------------------------------------
DEVICE_C2!C
              
 
------------------------------------------------------------------------------*/
/*
#include "main.h"
#include "xdata.h"
#include "display.h"
#include "engine.h"
#include "digitals.h"
#include "essential.h"
#include "ports.h"        
#include "timedate.h"
#include "watchdog.h"
#include "_timedate.h"



void    ResetDataC1(void)
{
  Clear();
  wOffsCurr = wBaseCurr;
  wPercentC2 = 0;

  ibValue7 = 0;
  memset(&mpValue71, 0, sizeof(mpValue71));
}


void    ResetDataC2(void)
{
  wBaseLast = wOffsCurr;

  ibValue7 = 0;
  memset(&mpValue72, 0, sizeof(mpValue72));
}


void    QueryHeaderC0_6(uint  wT)
{
  HideCurrTime(1);

  tiAlt = tiDigPrev;
  dwBuffC = DateToHouIndex();

  dwBuffC -= wT;

  HouIndexToDate(dwBuffC);
  tiDig = tiAlt;


  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(40);

  PushChar(tiDig.bMonth);
  PushChar(tiDig.bDay);
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);

  RevQueryIO(4+8*6+2, 3+3+2);
}


void    QueryHeaderC1_6(void)
{
  sprintf(szLo,"чтение     ");
  //x_str("\n QUERY MAIN"); x_inthex(wBaseCurr); x_time_dig();

  QueryHeaderC0_6(wBaseCurr);
}


void    QueryHeaderC2_6(void)
{
  sprintf(szLo,"проверка %bu ",ibHouCheck+1);
  //x_str("\n QUERY TEST"); x_inthex(wBaseLast); x_time_dig(); 

  QueryHeaderC0_6(wBaseLast);
}


void    SaveHeaderC(uchar  i)
{
  vValue71.tiSelf = tiDig;
  vValue71.bSelf = 0xFF;

  InitPop(4+i*8);                                    
  for (ibCan=0; ibCan<4; ibCan++)        
  {
    wBuffD  = PopChar();
    wBuffD += PopChar()*0x100;

    vValue71.mpwSelf[ibCan] = wBuffD;
  }

  //x_str("\n"); x_bytedec(ibValue7); x_value1(); ResetWatchdog();
}


void    SaveHeaderC1(uchar  i)
{ 
  SaveHeaderC(i);
  mpValue71[ibValue7++] = vValue71;
}


void    SaveHeaderC2(uchar  i)
{ 
  SaveHeaderC(i);
  mpValue72[ibValue7++] = vValue71;
}


void    ShowPercentC(uchar  bT)
{
  ShowProgress(28, bT);
}


bit     PushDataC1_6()
{
uchar i;

  ShowPercentC((ulong)100*(++wPercentC2)/(bVALUE7_BLOCKS*(mpbHouCheck[ibDig]+1)));

  for (i=0; i<6; i++)
  {
    tiAlt = tiDigPrev;
    dwBuffC = DateToHouIndex();

    dwBuffC += 5;
    dwBuffC -= (wBaseCurr + i);

    HouIndexToDate(dwBuffC);
    tiDig = tiAlt;

    if (dwBuffC < dwValueC) {     
      SaveHeaderC1(5-i);
    }
  }
  
  wBaseCurr += 6;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}


bit     PushDataC2_6()
{
uchar i;

  ShowPercentC((ulong)100*(++wPercentC2)/(bVALUE7_BLOCKS*(mpbHouCheck[ibDig]+1)));

  for (i=0; i<6; i++)
  {
    tiAlt = tiDigPrev;
    dwBuffC = DateToHouIndex();

    dwBuffC += 5;
    dwBuffC -= (wBaseLast + i);

    HouIndexToDate(dwBuffC);
    tiDig = tiAlt;

    if (dwBuffC < dwValueC) {     
      SaveHeaderC2(5-i);
    }
  }
  
  wBaseLast += 6;
  if (wBaseLast > wHOURS) return(0);

  return(1);
}


bit     TestDataC0_6(void)
{
uchar i;

  for (i=0; i<bVALUE7_REAL_SIZE; i++)
  {
    vValue71 = mpValue71[i];
    vValue72 = mpValue72[i];

    //x_str("\n"); x_bytedec(i); x_value1(); x_value2(); ResetWatchdog();

    if (vValue71.tiSelf.bSecond != vValue72.tiSelf.bSecond) return 1;
    if (vValue71.tiSelf.bMinute != vValue72.tiSelf.bMinute) return 2;
    if (vValue71.tiSelf.bHour   != vValue72.tiSelf.bHour)   return 3;
    if (vValue71.tiSelf.bDay    != vValue72.tiSelf.bDay)    return 4;
    if (vValue71.tiSelf.bMonth  != vValue72.tiSelf.bMonth)  return 5;
    if (vValue71.tiSelf.bYear   != vValue72.tiSelf.bYear)   return 6;

    if (vValue71.mpwSelf[0] != vValue72.mpwSelf[0]) return 7;
    if (vValue71.mpwSelf[1] != vValue72.mpwSelf[1]) return 8;
    if (vValue71.mpwSelf[2] != vValue72.mpwSelf[2]) return 9;
    if (vValue71.mpwSelf[3] != vValue72.mpwSelf[3]) return 10;
  }

  return 0;
}


bit   SaveDataC_7(uchar  i)
{
  vValue71  = mpValue71[i];
  tiDig = vValue71.tiSelf; 
  //x_str("\n"); x_bytedec(i); x_value1(); ResetWatchdog(); 
  if (vValue71.bSelf == 0) return 1;


  sprintf(szLo," %02bu    %02bu.%02bu.%02bu", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(1); 


  ShowProgressDigHou();      

  for (ibCan=0; ibCan<4; ibCan++) {
    mpwChannels[ibCan] = vValue71.mpwSelf[ibCan];
  }

  tiAlt = tiDig;
  if (IsDefect(ibDig)) MakeSpecial();
  return(MakeStopHou(0)); 
}


bit   SaveDataC0_6()
{
uchar i;

  for (i=0; i<bVALUE7_REAL_SIZE; i++) {
    ResetWatchdog();
    if (SaveDataC_7(i) == 0) return 0;
  }

  return 1;
}
*/
