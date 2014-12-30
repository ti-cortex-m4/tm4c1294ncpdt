/*------------------------------------------------------------------------------
GAPS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../engine.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "../ports.h"
#include        "tariffs.h"



//                                           0123456789ABCDEF
static char const       szNoGaps[]        = "  нет периодов  ",
                        szGapError[]      = " ошибка !";


static time const       tiGap0 = { 0, 0, 0, 14, 4, 0 };
static time const       tiGap1 = { 1, 0, 0, 14, 10, 0 };



uchar   GetGapSize(void) 
{
  return( mpgaGaps.bSize );
}


void    SetGapSize(uchar  bSize) 
{
  mpgaGaps.bSize = bSize;
}



void    GetGapDate(uchar  ibGap) 
{
  tiGap = mpgaGaps.mptiDate[ibGap];
}


void    SetGapDate(uchar  ibGap) 
{
  mpgaGaps.mptiDate[ibGap] = tiGap;
}



uint    GetDayIndex_Alt(void) 
{
uchar   i;
uint    j;

  j = tiAlt.bDay - 1; 

  for (i=1; i<tiAlt.bMonth; i++)
    j += mpbDaysInMonth[i - 1];

  return j;
}


uint    GetDayIndex_Gap(void) 
{
uchar   i;
uint    j;

  j = tiGap.bDay - 1; 

  for (i=1; i<tiGap.bMonth; i++)
    j += mpbDaysInMonth[i - 1];

  return j;
}


uchar   DaysInMonth_Gap(void)
{
  return mpbDaysInMonth[tiAlt.bMonth - 1];
}



void    ResetGaps(void)
{
uchar i;

  tiGap = tiZero;
  for (i=0; i<bGAPS; i++)
    SetGapDate(i);

  tiGap = tiGap0;
  SetGapDate(0);

  tiGap = tiGap1;
  SetGapDate(1);

  SetGapSize(2);

  boGapsFlag = boFalse;
}


void    MakeGaps(void)
{
uchar   i;
uint    j;

  if (GetGapSize() == 0)
  {
    for (j=0; j<sizeof(mpbGaps); j++)
      mpbGaps[j] = 0;
  }
  else
  { 
    GetGapDate(0);
    for (j=0; j<365; j++) 
      mpbGaps[j] = tiGap.bSecond;

    for (i=0; i<GetGapSize(); i++) 
    {
      GetGapDate(GetGapSize()-1-i);

      for (j=0; j<=GetDayIndex_Gap(); j++)
        mpbGaps[j] = tiGap.bSecond;
    }
  }
}



void    ShowGapName(uchar  ibMode)
{
  if ((ibMode >= 0) && (ibMode < 12))
    sprintf(szLo+7, "период %u" , ibMode+1);
  else
    strcpy(szLo+7, szGapError);
}



void    ShowGap(uchar  ibGap)
{
  if (GetGapSize() > 0)
  {
    GetGapDate(ibGap);
   
    sprintf(szLo,"%2u.%02u", tiGap.bDay, tiGap.bMonth);

    ShowGapName(tiGap.bSecond);

    sprintf(szHi+11,"%2u/%-2u", ibGap+1, GetGapSize());
  }
  else ShowLo(szNoGaps);    
}



#ifndef MODBUS

void    OutGaps1(void) 
{
  InitPushCRC();
  PushChar(boGapsFlag);
  Push(&mpgaGaps, sizeof(mpgaGaps));
  Output(1+sizeof(mpgaGaps));
}


void    OutGaps2(void) 
{
  if (enGlobal == GLB_PROGRAM) MakeGaps();

  InitPushCRC();
  PushChar(boGapsFlag);
  tiAlt = *PGetCurrTimeDate();
  Push(&tiAlt, sizeof(time));
  PushChar(mpbGaps[GetDayIndex_Alt()]);
  Push(&mpbGaps, sizeof(mpbGaps));
  Output(1+sizeof(time)+1+sizeof(mpbGaps));
}

#endif
