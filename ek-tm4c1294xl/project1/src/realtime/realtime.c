/*------------------------------------------------------------------------------
REALTIME.C

TODO ��������� ��������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_energy.h"
#include        "next_second.h"
#include        "next_minute1.h"
#include        "next_minute3.h"
#include        "next_minute30.h"
#include        "next_day.h"
#include        "next_month.h"
#include        "next_year.h"
#include        "../rtc.h"
#include        "../impulses/impulses.h"
#include        "../energy.h"
#include        "../health.h"
#include        "../digitals/digitals.h"
#include        "../digitals/profile.h"



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



void    InitRealtime(void)
{
}


void    StartRealtime(void)
{
uchar    c;
real     re;

  ibSoftMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = (GetCurrTimeDate()->bMonth) - 1;

  cbSummer = 0;
  cbWinter = 0;

  DisableImpulses();
  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);
  EnableImpulses(); // TODO EnableImpulses

  MakeCurrHouCan();

  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
    	re = GetCanReal(mpreCount,c);
      SetCanReal(mpreCntMonCan[ ibSoftMon ], c, &re);
    }
  }
}


/*
// ��������� ��������� ��������� � ����������� �������
bit     NexttimeOff(void)
{
uchar   i;

  cbWaitQuery = 0;

  fProfile = 0;
  fCurrent = 0;

  fSeason  = 0;

  if (GetLabelXDATA() == 0)
    return(1);
  else
  {
    // ����������� ������� ��������� �������
    cbPowerOn++;
    // ��������� ����� ���������� �������
    tiPowerOff = tiCurr;

    i = 0;
    while (1)
    {
      ResetWDT();

      // ������ �������� �������
      tiKey = *PGetCurrTimeDate();
      // �������� ������� ��� ������������ ���������
      tiCurr.bSecond = tiKey.bSecond;
       
      // ��������� ����� ��������� �������
      tiPowerOn = tiKey;

      if (memcmp(&tiCurr, &tiKey, sizeof(time)) == 0)
        return(1);

      // ������� ����� � ���������� � ������
      if (++tiCurr.bMinute >= 60)
      {
        tiCurr.bMinute = 0;
        if (++tiCurr.bHour >= 24)
        {
          tiCurr.bHour = 0;

          // ���������� ����� ���������� �������
          if (++i > 30) return(0);

          tiAlt = tiCurr;
          if (++tiCurr.bDay > DaysInMonth())
          {
            tiCurr.bDay = 1;
            if (++tiCurr.bMonth > 12)
            {
              tiCurr.bMonth = 1;
              tiCurr.bYear++;
            }
          }
        }
      }

      // ��������� ��������� �������
      ProcessTime();
/ *
      sprintf(szHi,"����   %02bu.%02bu.%02bu",
              tiCurr.bDay,   
              tiCurr.bMonth,
              tiCurr.bYear);

      sprintf(szLo,"�����  %02bu:%02bu:%02bu",
              tiCurr.bHour,
              tiCurr.bMinute,
              tiCurr.bSecond);
* /
      sprintf(szHi," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiCurr.bHour,
                     tiCurr.bMinute,
                     tiCurr.bDay,   
                     tiCurr.bMonth,
                     tiCurr.bYear);

      sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiKey.bHour,
                     tiKey.bMinute,
                     tiKey.bDay,   
                     tiKey.bMonth,
                     tiKey.bYear);

      // ������ ���������� �������
      tiPrev = tiCurr;
    }
  }
}



// ��������� ��������� ��������� � ����������� ������� � ���������� �� �������� �����
void    InitNexttime(void)
{
  if (GetLabelRTC() == 0) TestError(szBadRTC1);

  PGetCurrTimeDate();
  if (TrueCurrTimeDate() == 0) // TestError(szBadRTC2);
  {
    ShowHi(szAlarm); 
    ShowLo(szBadRTC2); LongBeep(); DelayMsg();
    return;
  }

  fSummer = 0;
  fWinter = 0;

  AddSysRecord(EVE_PREVNEXTTIME2);
  NexttimeOff();
  AddSysRecord(EVE_POSTNEXTTIME);

  if (fSummer == 1)
  {
    if (++tiCurr.bHour >= 24)
    {
      tiCurr.bHour = 0;

      tiAlt = tiCurr;
      if (++tiCurr.bDay > DaysInMonth())
      {
        tiCurr.bDay = 1;
        if (++tiCurr.bMonth > 12)
        {
          tiCurr.bMonth = 1;
          tiCurr.bYear++;
        }
      }
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }

  if (fWinter == 1)
  {
    if (tiCurr.bHour > 0)
      tiCurr.bHour--;
    else
    {
      tiCurr.bHour = 23;
      if (tiCurr.bDay > 1)
        tiCurr.bDay--;
      else
      {
        if (tiCurr.bMonth > 1)
          tiCurr.bMonth--;
        else
        {
          tiCurr.bMonth = 12;  
          tiCurr.bYear--; 
        }

        tiAlt = tiCurr;
        tiCurr.bDay = DaysInMonth();             
      } 
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }
}
*/


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
