/*------------------------------------------------------------------------------
REALTIME.C

TODO ��������� ��������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../rtc.h"
#include        "../health.h"
#include        "next_second.h"
#include        "next_minute1.h"
#include        "next_minute3.h"
#include        "next_minute30.h"
#include        "next_day.h"
#include        "next_month.h"
#include        "next_year.h"
#include        "realtime_storage.h"



// ������� �������� �� �������� ����� � ������� �����
bool                    fSeason;

// �������� �������� �� �������� ����� ��� ����������� ���������
bool                    fSummer, fWinter;

// ������� ������ � �������� ������
bool                    fActive;



// TODO rename ���������� ������ �������� ��������
uchar   GetCurrHouIndex(void)
{
  return(tiCurr.bHour*2 + tiCurr.bMinute/30);
}


// TODO rename ���������� ������ �� ������ ������� ��������� ����� �����
uint    GetDayHouIndex(uchar  bDay)
{
uchar   i;
uint    j;

  // ������ �� ������ ������� ������� �����
  j = (wHOURS+iwHardHou-GetCurrHouIndex()) % wHOURS;

  // ������� �� ������ �������� ����� �����
  for (i=0; i<bDay; i++) j = (wHOURS+j-48) % wHOURS;

  // ������ �� ������ ������� ��������� �����
  return(j);
}



uchar   PrevSoftMnt(void)
{
  if (ibSoftMnt > 0) return(ibSoftMnt - 1);
  else               return(bMINUTES-1);
}



uchar   PrevSoftHou(void)
{
  if (ibSoftHou > 0) return(0);
  else               return(1);
}


uint    PrevHardHou(void)
{
  if (iwHardHou > 0) return(iwHardHou - 1);
  else               return(wHOURS-1);
}



uchar   PrevSoftDay(void)
{
  if (ibSoftDay > 0) return(0);
  else               return(1);
}


uchar   PrevHardDay(void)
{
  if (ibHardDay > 0) return(ibHardDay - 1);
  else               return(bDAYS-1);
}



uchar   PrevSoftMon(void)
{
  if (ibSoftMon > 0) return(0);
  else               return(1);
}


uchar   PrevHardMon(void)
{
  if (ibHardMon > 0) return(ibHardMon - 1);
  else               return(bMONTHS-1);
}



void    ProcessTime(void)
{
  // ������� �� ��������� �������
  if (tiCurr.bSecond != tiPrev.bSecond)
  {
    NextSecond();
  }


  // ������� �� ��������� ������
  if (tiCurr.bMinute != tiPrev.bMinute)
  {
    NextMinute1();
  }


  // ������� �� ��������� ��� ������
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
    NextMinute3();
  }


  // ������� �� ��������� �������
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
    if ((tiCurr.bDay   == tiSummer.bDay)   &&
        (tiCurr.bMonth == tiSummer.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 0))
    {
      cbSummer++;

      if (fActive == 1)
      {
        tiCurr.bHour = 3;
        SetCurrTimeDate(&tiCurr);
      }
      else fSummer = 1;

      fSeason = 1;

      NextMinute30();
      NextMinute30();
      NextMinute30();
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 3)               && (fSeason == 0))
    {
      cbWinter++;

      if (fActive == 1)
      {
        tiCurr.bHour = 2;
        SetCurrTimeDate(&tiCurr);
      }
      else fWinter = 1;

      fSeason = 1;
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 1))
      { }
    else
      NextMinute30();
  }


  // ������� �� ��������� �����
  if (tiCurr.bDay != tiPrev.bDay)
  {
    fSeason = 0;
    NextDay();
  }


  // ������� �� ��������� �����
  if (tiCurr.bMonth != tiPrev.bMonth)
  {
  	NextMonth();
  }


  // ������� �� ��������� ���
  if (tiCurr.bYear != tiPrev.bYear)
  {
    NextYear();
  }
}



// ��������� ��������� ��������� � �������� �������
void    Realtime(void)
{
time    ti;

//  if (GetLabelRTC() == 0) {
//	boHealthLabelRTC = FALSE;
//    return;
//  }
//  boHealthLabelRTC = TRUE;

  ti = *GetCurrTimeDate();
  if (TrueCurrTimeDate(&ti) == 0) {
    boHealthTimeRTC = FALSE;
	return;
  }
  boHealthTimeRTC = TRUE;

  if (tiCurr.bSecond != ti.bSecond)
  {
    tiCurr = ti;

    if (enGlobal != GLB_PROGRAM)
    {
      fActive = 1;
      ProcessTime();
    }
    else
    {
//      fProfile = 0;
//      fCurrent = 0;
    }

    tiPrev = tiCurr;
  }
}
