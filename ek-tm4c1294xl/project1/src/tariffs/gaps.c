/*------------------------------------------------------------------------------
GAPS.C

 Тарифные периоды: Отчет №66 от 17_08_2010
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../flash/files.h"
#include        "../time/timedate.h"
#include        "tariffs.h"
#include        "gaps.h"



static time const       tiGap0 = { 0, 0, 0, 14,  4, 0 };
static time const       tiGap1 = { 1, 0, 0, 14, 10, 0 };

file const              flGapsFlag = {GAPS_FLAG, &boGapsFlag, sizeof(boolean)};
file const              flGaps = {GAPS, &gaGaps, sizeof(gaGaps)};



void    InitGaps(void)
{
	LoadFile(&flGapsFlag);
	LoadFile(&flGaps);
}


void    ResetGaps(void)
{
  boGapsFlag = FALSE;
  SaveFile(&flGapsFlag);

  memset(&gaGaps, 0, sizeof(gaGaps));

  tiGap = tiGap0;
  SetGapDate(0);

  tiGap = tiGap1;
  SetGapDate(1);

  SetGapSize(2);
	SaveFile(&flGaps);
}



uchar   GetGapSize(void) 
{
  return( gaGaps.bSize );
}


void    SetGapSize(uchar  bSize) 
{
  gaGaps.bSize = bSize;
}



void    GetGapDate(uchar  ibGap) 
{
  tiGap = gaGaps.mptiDate[ibGap];
}


void    SetGapDate(uchar  ibGap) 
{
  gaGaps.mptiDate[ibGap] = tiGap;
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

      for (j=0; j<=GetDayIndexMD(tiGap.bMonth, tiGap.bDay); j++)
        mpbGaps[j] = tiGap.bSecond;
    }
  }
}
