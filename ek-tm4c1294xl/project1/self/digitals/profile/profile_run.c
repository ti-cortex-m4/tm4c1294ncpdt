/*------------------------------------------------------------------------------
PROFILE_RUN!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_schedule.h"
#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../serial/auto_flow.h"
#include "../../serial/dtr.h"
#include "../../sensors/device_k.h"
#include "../../sensors/sensor21/device_p.h"
#include "../../sensors/sensor26/device_u.h"
#include "../../sensors/sensor36/device36.h"
#include "../../sensors/sensor39/dlms.h"
#include "../../sensors/device_q.h"
#include "../../sensors/device_w.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/digitals_pause.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/dsbl_answer.h"
#include "../../digitals/schedule/enbl_hours.h"
#include "../../digitals/skip_failure.h"
#include "../../special/special.h"
#include "../../special/recalc.h"
#include "../../special/recalc3.h"
#include "../../time/decret.h"
#include "../../flash/records.h"
#include "../limits.h"
#include "profile_link.h"
#include "profile_run.h"



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
        (diCurr.bDevice == 22) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24) ||
        (diCurr.bDevice == 26) || (diCurr.bDevice == 28) ||
        (diCurr.bDevice == 27) ||
        (diCurr.bDevice == 29) || (diCurr.bDevice == 30) ||
        (diCurr.bDevice == 31) || (diCurr.bDevice == 32) || (diCurr.bDevice == 33) ||
        (diCurr.bDevice == 34) ||
        (diCurr.bDevice == 35) ||
        (diCurr.bDevice == 36) || (diCurr.bDevice == 37) ||
        (diCurr.bDevice == 38) || (diCurr.bDevice == 39) ||
        (diCurr.bDevice == 40))
    {
      if (mpboReadyCan[ibDig] == false)
      {
        if (mpboEnblCan[ibDig] == false)
        {
          ShowCanalNumber(ibDig);
          ShowLo(szDisabledCan); if (boHideMessages == false) DelayInf();
          AddDigRecord(EVE_CANAL_DISABLED);
        }
        else if ((GetEnblPrtHou(diCurr.ibPort, GetCurrHouIndex()) == false) && (boManualProfile == false))
        {
          ShowCanalNumber(ibDig);
          sprintf(szHi+14,"%02u",GetCurrHouIndex());
          ShowLo(szDisabledHou); if (boHideMessages == false) DelayMsg();
          AddDigRecord(EVE_PROFILE_DISABLED);
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


  boRecalcCurr = mpboRecalcHou[GetCurrHouIndex()];

  AddDigRecord(EVE_PROFILE2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILE);

  if (boManualProfile == false)
  {
    AddDigRecord(EVE_PROFILEOPEN);
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOPEN);
  }
  else
  {
    AddDigRecord(EVE_SPECIALOPEN);
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_SPECIALOPEN);
  }


  HideCurrTime(1);
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
    case 26:
    case 28: SetNext(DEV_START_U2);  break;
#endif

#ifndef SKIP_V
    case 27: SetNext(DEV_START_V2);  break;
#endif

#ifndef SKIP_W
    case 29:
    case 30: SetNext(DEV_START_W2);  break;
#endif

#ifndef SKIP_31
    case 31: SetNext(DEV_START_31P); break;
#endif

#ifndef SKIP_32
    case 32: SetNext(DEV_START_32P); break;
#endif

#ifndef SKIP_33
    case 33: SetNext(DEV_START_33P); break;
#endif

#ifndef SKIP_34
    case 34: SetNext(DEV_START_34P); break;
#endif

#ifndef SKIP_35
    case 35: SetNext(DEV_START_35P); break;
#endif

#ifndef SKIP_36
    case 36:
    case 37: SetNext(DEV_START_36P); break;
#endif

#ifndef SKIP_38
    case 38: 
    case 39: SetNext(DEV_START_38P); break;
#endif

#ifndef SKIP_40
    case 40: SetNext(DEV_START_40P); break;
#endif
  }

  exExtended = EXT_PROFILE_30MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunProfile(bool  _fCtrlHou)
{
  if (boEnblProfile != true)
    BlockProgramExt(bSET_ENBL_PROFILE);
  else if (IsAutoFlowTime())
    BlockBy(szByAutoFlow);
  else
  {
#ifdef  FLOW
    CloseFlow();
#endif

    fCurrCtrl = _fCtrlHou;
    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    cwHouLength = 0;

//    if (boDTREnable == true) DTROff_All();

    if (StartProfile(0) == 1) { OpenSpecial(); DisableAnswer(); } else { Work(); OK(); }
  }

}



void    NextProfile(void)
{
  if ((boHideMessages == false) && !SkipFailure_IsFailure())
  {
    Clear(); sprintf(szLo+1,"принято: %04u",cwHouRead); DelayMsg();
  }

  LoadCurrDigital(ibDig);
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1) mpcwProfile_OK[c]++;
  }

  AddDigRecord(EVE_PROFILE_OK2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOK);


  if (cwHouRead == 0)
  {
    // запрещаем опрашивать другие каналы, принадлежащие текущему счётчику
    LoadCurrDigital(ibDig);
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1) mpboReadyCan[c] = true;
    }

    if ((boHideMessages == false) && !SkipFailure_IsFailure())
    {
      ShowLo(szNoData); DelayMsg();
    }
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
    case 26:
    case 28: QueryCloseU();  break;
#endif

#ifndef SKIP_W
    case 29:
    case 30: QueryCloseW();  break;
#endif

#ifndef SKIP_36
    case 36:
    case 37: QueryClose36();  break;
#endif

#ifndef SKIP_39
    case 39: DISC();  break;
#endif
  }

  if (StartProfile(ibDig+1) == 0) // опрос завершён
  {
    ShowHi(szWorkDone);
    sprintf(szLo+4,"за %u:%02u", (uint)(cwHouLength / 60), (uchar)(cwHouLength % 60)); if (boHideMessages == false) DelayMsg();

    SetCurr(DEV_BEGIN);

    CloseSpecial();
    CloseSpecialBuff();

    AddDigRecord(EVE_PROFILECLOSE2);

//    if (boDTREnable == true) DTROff_All();

    if (boRecalcCurr == true)
    {
      AddDigRecord(EVE_RECALC20);
      Recalc(1,1);
      AddDigRecord(EVE_RECALC21);
    }
    else if (boRecalcMaxPowCurrDay == true)
    {
      Recalc_MaxPowCurrDay();
    }

//    if ((boRecalcCurr == true) && (boRecalcEnable == true))
//    {
//      Recalc_Cust();
//    }

    Work();
    OK();

    boManualProfile = false;

    ibPortPause = 0xFF;

    EnableAnswer();

//    if (mpboCheckupHou[GetCurrHouIndex()] == true) cbCheckupRun = 10;
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;
}



// аварийный переход на следующий канал
void    ErrorProfile(void)
{
  IncProfileLinkErr(diCurr.ibPort, GetCurrHouIndex());

  SaveDisplay();

  ShowHi(szWarning);
  Clear();
  sprintf(szLo,"запроса %02X.%02X.%02X",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  LoadCurrDigital(ibDig);
  uchar ibCan;
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
    if (CompareCurrPrevLines(ibDig, ibCan) == 1) mpboReadyCan[ibCan] = true;
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
