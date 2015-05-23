/*------------------------------------------------------------------------------
CHECKUP_B.C 


------------------------------------------------------------------------------*/
/*
#include "main.h"
#include "xdata.h"
#include "checkup.h"
#include "keyboard.h"
#include "display.h"
#include "delay.h"
#include "engine.h"
#include "essential.h"
#include "essential2.h"
#include "ports.h"        
#include "device_b.h"        
#include "digitals.h"        
#include "checkup.h"        
#include "timedate.h"
#include "_timedate.h"



void    DecPtrB_Checkup(uchar  j)
{
uchar   i;

  for (i=0; i<j; i++)
    (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
}



void    QueryEnergyPrevDayB(void)
{
  QueryEnergyB(0x50);
}


void    QueryEnergyPrevMonB(uchar  ibMonPrev)
{
  QueryEnergyB(0x30 | ((12 + tiCurr.bMonth - ibMonPrev - 1)% 12 + 1));
}



void    ReadEnergyPrevDayB(uchar  ibDay)
{
  for (ibCan=0; ibCan<4; ibCan++)
    mpdwChannelsA[ibCan] = mpdwChannelsCheckup[ibDay][ibCan];
}


void    ReadTopBOld_Checkup(void)
{ 
  wBaseCurr = InBuff(1)*0x100 + InBuff(2);

  StartRefill();
}



void    InitHeaderB_Checkup1(void)
{
  memset(&mpdwChannelsCheckup, 0, sizeof(mpdwChannelsCheckup));

  Clear();
  sprintf(szLo+3, "сутки: %bu", mpbCheckupLimitD[ibDig]);
}


void    ShowProgressDigHouB_Checkup1(uchar  ibDay)
{
uint    i;

  i = (ulong)100*ibDay/(mpbCheckupLimitD[ibDig]);
  if (i > 100) i = 100;

  ShowProgress(12,i);

  if (mpbCheckupLimitD[ibDig] > 1)
  {
    szHi[9]  = '#';
    szHi[10] = '1';
  }
}


bit    ReadHeaderB_Checkup1(void)
{
  NoShowTime(1);

  InitPop(2);  
  tiDig.bHour   = FromBCD( PopChar() );
  tiDig.bMinute = FromBCD( PopChar() );
  tiDig.bDay    = FromBCD( PopChar() );
  tiDig.bMonth  = FromBCD( PopChar() );
  tiDig.bYear   = FromBCD( PopChar() );

  if ((tiDig.bDay   == tiSummer.bDay) &&
      (tiDig.bMonth == tiSummer.bMonth))
  {
    if ((tiDig.bHour   == 3) && 
        (tiDig.bMinute == 0))
    {
      tiDig.bHour   = 2;  
      tiDig.bMinute = 0;
    }
  }


  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем время/дату часового блока
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0)                        // обрабатываем неполный получасовой блок
  {
    tiDig.bMinute = (tiDig.bMinute / 30)*30;
    if (SearchDefHouIndex() == 0) { szLo[4] = '?'; return(1); }

    iwDigHou = (wHOURS+iwDigHou+1)%wHOURS;   
  }
  else if (SearchDefHouIndex() == 0) { szLo[4] = '?'; return(1); } 


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // время записи должно соответсвовать началу получасового блока

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  HouIndexToDate(dwBuffC);


  tiDig = tiAlt;                                        // save time


  dwValMax = DateToDayIndex(); 

  tiAlt = tiCurr;
  dwValCurr = DateToDayIndex(); 

  if (dwValMax > dwValCurr)
  {
    return (0);
  }
  else
  {
    dwBuffC = dwValCurr - dwValMax;
    if (dwBuffC > 0xFF) return (0);
    ibGrp = dwBuffC;
    if (ibGrp > mpbCheckupLimitD[ibDig]) return (0);
  }


  tiAlt = tiDig;                                        // load time


  sprintf(szLo," %02bu:%02bu",tiAlt.bHour,tiAlt.bMinute);

  ShowProgressDigHouB_Checkup1(ibGrp);      


  InitPop(8);                              
  for (ibCan=0; ibCan<4; ibCan++)        
  {
    wBuffD  = PopChar();
    wBuffD += PopChar()*0x100;

    if (wBuffD == 0xFFFF) wBuffD = 0;

    mpdwChannelsCheckup[ibGrp][ibCan] += wBuffD;
  }

  return(1);
}



void    InitHeaderB_Checkup2(void)
{
uchar   i,j;

  j = 0;
  daAlt = mpCheckupDays[j];
  DateToTimeAlt();
  dwCurr = DateToDayIndex(); 

  for (i=0; i<cbCheckupDays; i++)
  {
    daAlt = mpCheckupDays[i];
    DateToTimeAlt();
    dwPrev = DateToDayIndex(); 

    if (dwPrev < dwCurr) { dwCurr = dwPrev; j = i; }
  }

  daAlt = mpCheckupDays[j];
  DateToTimeAlt();
  dwValMax = DateToDayIndex(); 

  tiAlt = tiCurr;
  dwValCurr = DateToDayIndex(); 

  Clear();
  sprintf(szLo+2, "до: %02bu.%02bu.%02bu", daAlt.bDay, daAlt.bMonth, daAlt.bYear);
}


void    ShowProgressDigHouB_Checkup2(void) 
{
uint    i;

  dwBuffC = DateToDayIndex(); 

  i = (ulong)100*(dwValCurr - dwBuffC)/(dwValCurr - dwValMax);
  if (i > 100) i = 100;

  ShowProgress(12,i);

  if (mpbCheckupLimitD[ibDig] > 1)
  {
    szHi[9]  = '#';
    szHi[10] = '2';
  }
}


bit    ReadHeaderB_Checkup2(void)
{
  NoShowTime(1);

  InitPop(2);  
  tiDig.bHour   = FromBCD( PopChar() );
  tiDig.bMinute = FromBCD( PopChar() );
  tiDig.bDay    = FromBCD( PopChar() );
  tiDig.bMonth  = FromBCD( PopChar() );
  tiDig.bYear   = FromBCD( PopChar() );

  if ((tiDig.bDay   == tiSummer.bDay) &&
      (tiDig.bMonth == tiSummer.bMonth))
  {
    if ((tiDig.bHour   == 3) && 
        (tiDig.bMinute == 0))
    {
      tiDig.bHour   = 2;  
      tiDig.bMinute = 0;
    }
  }


  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем время/дату часового блока
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0)                        // обрабатываем неполный получасовой блок
  {
    tiDig.bMinute = (tiDig.bMinute / 30)*30;
    if (SearchDefHouIndex() == 0) { szLo[4] = '?'; return(1); }

    iwDigHou = (wHOURS+iwDigHou+1)%wHOURS;   
  }
  else if (SearchDefHouIndex() == 0) { szLo[4] = '?'; return(1); } 


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // время записи должно соответсвовать началу получасового блока

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  HouIndexToDate(dwBuffC);


  tiDig = tiAlt;                                        // save time


  ShowProgressDigHouB_Checkup2();      
  
  dwCurr = DateToDayIndex(); 
  if (dwCurr < dwValMax) return (0);                    // опрос завершен


  daAlt.bDay   = tiDig.bDay;
  daAlt.bMonth = tiDig.bMonth;
  daAlt.bYear  = tiDig.bYear;
  if (IsCheckupDayAdded() == 0) { szLo[4] = '*'; StartRefill(); return(1); } // не нужно проверять эти сутки


  ibXmin = ibDig;
  ibXmax = ibDig;
  iwAmin = iwDigHou;
  iwAmax = iwDigHou;

  CheckupClearCanals();


  tiAlt = tiDig;                                        // load time


  InitPop(8);                              
  for (ibCan=0; ibCan<4; ibCan++)        
  {
    wBuffD  = PopChar();
    wBuffD += PopChar()*0x100;

    if (wBuffD == 0xFFFF) wBuffD = 0;

    mpwChannels[ibCan] = wBuffD;
  }

  MakeRefillWinter();
  MakeSpecial();
  if (boRefillDisable == FALSE) MakeRefill();

  return(1);
}
*/
