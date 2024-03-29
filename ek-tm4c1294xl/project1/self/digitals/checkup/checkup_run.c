/*------------------------------------------------------------------------------
CHECKUP_RUN!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_checkup.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../serial/dtr.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/digitals_pause.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/dsbl_answer.h"
#include "../../special/special.h"
#include "../../time/decret.h"
#include "../../flash/records.h"
#include "checkup.h"



bool    StartCheckup(uchar  ibCanal)
{
  ibDig = ibCanal;
  while (ibDig < bCANALS)
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice == 2) || (diCurr.bDevice == 3))
    {
      if (mpboReadyCan[ibDig] == false)
      {
        if (mpboEnblCan[ibDig] == false)
        {
          ShowCanalNumber(ibDig);
          ShowLo(szDisabledCan); if (boHideMessages == false) DelayInf();
          AddDigRecord(EVE_CANAL_DISABLED);
        }
        else break;
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);


  if (IsWinter(tiCurr))
  {
    ShowHi(szNewSeason);
    ShowLo(szIsWinter);
    DelayMsg();

    Work();
    OK();
    return(0);
  }


  AddDigRecord(EVE_CHECKUP_START);
  //if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILE);

  HideCurrTime(1);
  ShowCanalNumber(ibDig);
  Clear();

  cwHouRead = 0;

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_B
    case 2:  SetNext(DEV_START_B4);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C4);  break;
#endif
  }

  exExtended = EXT_PROFILE_CHECKUP;
  MakePause(DEV_MODEM_START);
  return(1);
}



void    RunCheckup(bool  _fCheckupReadOnly)
{
#ifdef  FLOW
  CloseFlow();
#endif

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
  cwHouLength = 0;

  boCheckupReadOnly = (_fCheckupReadOnly == 1) ? true : false;
  ClearCheckup();

//  if (boDTREnable == true) DTROff_All();

  if (StartCheckup(0) == 1) { OpenSpecial(); DisableAnswer(); } else { Work(); OK(); }
}


/*
void    NexttimeCheckup(void)
{
  if (boCheckupEnable == true)
    RunCheckup(0);
}
*/


void    NextCheckup(void)
{/*
  if (boHideMessages == false)
  {
    Clear(); sprintf(szLo+1,"�������: %04u",cwHouRead);
    DelayMsg();
  }

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpcwProfile_OK[ibCan]++;
  }

  AddDigRecord(EVE_CHECKUP_NEXT);
  //if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOK);


  if (cwHouRead == 0)
  {
    // ��������� ���������� ������ ������, ������������� �������� ��������
    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpboReadyCan[ibCan] = true;
    }

    //ShowLo(szNoData); if (boHideMessages == false) DelayMsg();
  }

  Clear();


  if (StartCheckup(ibDig+1) == 0)
  {
    ShowHi(szWorkDone);
    sprintf(szLo+4,"�� %u:%02bu", (uint)(cwHouLength / 60), (uchar)(cwHouLength % 60)); if (boHideMessages == false) DelayMsg();

    SetCurr(DEV_BEGIN);

    OnHours();
    //AddDigRecord(EVE_PROFILECLOSE2);

    if (boDTREnable == true) DTROff_All();

    if (boCheckupRecalc == true)
    {
      AddDigRecord(EVE_RECALC20);
      Recalc(1,1);
      AddDigRecord(EVE_RECALC21);
    }

    Work(); OK();

    ibPortPause = 0xFF;

    EnableAnswer();
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;*/
}



void    ErrorCheckup(void)
{
uchar   ibCan;

  SaveDisplay();

  ShowHi(szWarning);
  Clear();
  sprintf(szLo,"������� %02X.%02X.%02X",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpcwProfile_Error[ibCan]++;
  }

  AddDigRecord(EVE_PROFILE_ERROR2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEERROR2);

  DelayMsg();
  LoadDisplay();


  // ��������� ���������� ������ ������, ������������� �������� ��������
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpboReadyCan[ibCan] = true;
  }

  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);
}



// ���������� ������� �� ��������� �����
void    DoneCheckup(void)
{
  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEDONE2);
}

