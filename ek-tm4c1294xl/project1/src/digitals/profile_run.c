/*------------------------------------------------------------------------------
PROFILE_RUN.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_direct.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_timedate.h"
#include        "../realtime/realtime.h"
#include        "../serial/ports.h"
#include        "../serial/flow.h"
#include        "../serial/dtr.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_status.h"
#include        "../digitals/digitals_pause.h"
#include        "../devices/devices.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/answer.h"
#include        "../digitals/enbl_hours.h"
#include        "../special/special.h"
#include        "../time/decret.h"
#include        "../flash/records.h"
#include        "limits.h"
#include        "profile_run.h"



bool    StartProfile(uchar  ibCanal)
{
  ibDig = ibCanal;

  while (ibDig < bCANALS)
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) ||
        (diCurr.bDevice ==  3) ||
        (diCurr.bDevice ==  4) ||
        (diCurr.bDevice ==  5) || (diCurr.bDevice ==  7) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice ==  9) || (diCurr.bDevice == 10) ||
        (diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25) ||
        (diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 21) ||
        (diCurr.bDevice == 22) || (diCurr.bDevice == 26) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24) ||
        (diCurr.bDevice == 99))
    {
      if (mpboReadyCan[ibDig] == FALSE)
      {
        if (mpboEnblCan[ibDig] == FALSE)
        {
          ShowCanalNumber(ibDig);
          ShowLo(szDisabledCan); if (boHideMessages == FALSE) DelayInf();
          AddDigRecord(EVE_CANAL_DISABLED);
        }
        else if ((GetEnblPrtHou(diCurr.ibPort, GetCurrHouIndex()) == FALSE) && (boManualProfile == FALSE))
        {
          ShowCanalNumber(ibDig);
          sprintf(szHi+14,"%02u",GetCurrHouIndex());
          ShowLo(szDisabledHou); if (boHideMessages == FALSE) DelayMsg();
          AddDigRecord(EVE_PROFILE_DISABLED);
        }
        else break;
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);



  if (IsWinter(&tiCurr))
  {
    ShowHi(szNewSeason);
    ShowLo(szIsWinter);
    DelayMsg();

    Work();
    OK();
    return(0);
  }


  // TODO boRecalcCurr = mpboRecalcHou[GetCurrHouIndex()];

  AddDigRecord(EVE_PROFILE2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILE);

  mpboDefEscV[ibDig] = FALSE;
  mpboDefEscS[ibDig] = FALSE;
  mpboDefEscU[ibDig] = FALSE;

  if (boManualProfile == FALSE)
  {
    AddDigRecord(EVE_PROFILEOPEN);
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOPEN);
  }
  else
  {
    AddDigRecord(EVE_SPECIALOPEN);
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_SPECIALOPEN);
  }


  HideCurrentTime(1);
  ShowCanalNumber(ibDig);
  Clear();

  cwHouRead = 0;

  // TODO fBreakRead = 0;

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  SetNext(DEV_START_A2);  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  SetNext(DEV_START_B2);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C2);  break;
#endif

#ifndef SKIP_D
    case 4:  SetNext(DEV_START_D2);  break;
#endif

#ifndef SKIP_E
    case 7:
    case 5:  SetNext(DEV_START_E2);  break;
#endif

#ifndef SKIP_F
    case 6:  SetNext(DEV_START_F2);  break;
#endif

#ifndef SKIP_G
    case 9:  SetNext(DEV_START_G2);  break;
#endif

#ifndef SKIP_H
    case 10: SetNext(DEV_START_H2);  break;
#endif

#ifndef SKIP_I
    case 11: SetNext(DEV_START_I2);  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: SetNext(DEV_START_K2);  break;
#endif

#ifndef SKIP_O
    case 20: SetNext(DEV_START_O2);  break;
#endif

#ifndef SKIP_P
    case 21: SetNext(DEV_START_P2);  break;
#endif

#ifndef SKIP_Q
    case 22: SetNext(DEV_START_Q2);  break;
#endif

#ifndef SKIP_R
    case 23: SetNext(DEV_START_R2);  break;
#endif

#ifndef SKIP_S
    case 24: SetNext(DEV_START_S2);  break;
#endif

#ifndef SKIP_T
    case 25: SetNext(DEV_START_T2);  break;
#endif

#ifndef SKIP_U
    case 26: SetNext(DEV_START_U2);  break;
#endif

#ifndef SKIP_Z
    case 99: SetNext(DEV_START_Z2);  break;
#endif
  }

  exExtended = EXT_PROFILE_30MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunProfile(bool  _fCtrlHou)
{
  if (boEnblProfile == TRUE)
  {
#ifdef  FLOW
    CloseFlow();
#endif

    fCurrCtrl = _fCtrlHou;
    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    cwHouLength = 0;

//    if (boDTREnable == TRUE) DTROff_All();

    if (StartProfile(0) == 1) { OpenSpecial(); DisableAnswer(); } else { Work(); OK(); }
  }
  else BlockProgramExt(bSET_ENBL_PROFILE);
}



void    NextProfile(void)
{
  if (boHideMessages == FALSE)
  {
    Clear();
    sprintf(szLo+1,"принято: %04u",cwHouRead);
    DelayMsg();
  }

  LoadCurrDigital(ibDig);
  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpcwProfile_OK[ibCan]++;
  }

  AddDigRecord(EVE_PROFILE_OK2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOK);


  if (cwHouRead == 0)
  {
    // запрещаем опрашивать другие каналы, принадлежащие текущему счётчику
    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpboReadyCan[ibCan] = TRUE;
    }

    ShowLo(szNoData); if (boHideMessages == FALSE) DelayMsg();
  }

  Clear();


  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_D
    case 4:  QueryCloseD(1); break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: QueryCloseK();  break;
#endif

#ifndef SKIP_P
    case 21: QueryCloseP();  break;
#endif

#ifndef SKIP_Q
    case 22: QueryCloseQ();  break;
#endif

#ifndef SKIP_U
    case 26: QueryCloseU();  break;
#endif
  }

  if (StartProfile(ibDig+1) == 0) // опрос завершён
  {
    ShowHi(szWorkDone);
    sprintf(szLo+4,"за %u:%02u", (uint)(cwHouLength / 60), (uchar)(cwHouLength % 60)); if (boHideMessages == FALSE) DelayMsg();

    SetCurr(DEV_BEGIN);

    CloseSpecial();

    AddDigRecord(EVE_PROFILECLOSE2);

//    if (boDTREnable == TRUE) DTROff_All();

    // TODO: recalc

    Work();
    OK();

    boManualProfile = FALSE;

    ibPortPause = 0xFF;

    EnableAnswer();

//    if (mpboCheckupHou[GetCurrHouIndex()] == TRUE) cbCheckupRun = 10;
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;
}



// аварийный переход на следующий канал
void    ErrorProfile(void)
{
uchar   ibCan;

  SaveDisplay();

  ShowHi(szWarning);
  Clear();
  sprintf(szLo,"запроса %02X.%02X.%02X",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
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


  // запрещаем опрашивать другие каналы, принадлежащие текущему счётчику
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpboReadyCan[ibCan] = TRUE;
  }

  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);
}


// нормальный переход на следующий канал
void    DoneProfile(void)
{
  NewLimits(); // переход границы со стороны счётчика

  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEDONE1);
}


// нормальный переход на следующий канал
void    DoneProfile_Stop(void)
{
  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEDONE2);
}
