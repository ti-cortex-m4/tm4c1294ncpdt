/*------------------------------------------------------------------------------
CURRENT_RUN!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../serial/auto_flow.h"
#include "../../realtime/realtime.h"
#include "../../sensors/device_k.h"
#include "../../sensors/sensor21/device_p.h"
#include "../../sensors/device_q.h"
#include "../../sensors/sensor26/device_u.h"
#include "../../sensors/device_w.h"
#include "../../sensors/sensor36/device36.h"
#include "../../sensors/sensor39/device39.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/digitals_pause.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/current/current.h"
#include "../../digitals/current/current2.h"
#include "../../digitals/phones2/phones2_z.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../kernel/array_mnt.h"



bool    StartCurrent(uchar  ibCanal)
{
  ibDig = ibCanal;

  while (ibDig < bCANALS)
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  3) ||
        (diCurr.bDevice ==  4) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice ==  9) ||
        (diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25) ||
        (diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 16) || (diCurr.bDevice == 17) ||
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19) ||
        (diCurr.bDevice == 21) ||
        (diCurr.bDevice == 22) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24) ||
        (diCurr.bDevice == 26) || (diCurr.bDevice == 28) ||
        (diCurr.bDevice == 27) ||
        (diCurr.bDevice == 29) || (diCurr.bDevice == 30) ||
        (diCurr.bDevice == 31) ||
        (diCurr.bDevice == 34) ||
        (diCurr.bDevice == 35) ||
        (diCurr.bDevice == 36) || (diCurr.bDevice == 37) ||
        (diCurr.bDevice == 38))
    {
      if (mpboReadyCan[ibDig] == false)
      {
        if (mpboEnblCan[ibDig] == false)
        {
          ShowCanalNumber(ibDig);
          ShowLo(szDisabledCan); if (boHideMessages == false) Delay(300);
        }
        else break;
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);


  HideCurrTime(1);
  ShowCanalNumber(ibDig);
  Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  SetNext(DEV_START_A3);  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  SetNext(DEV_START_B3);  break;
#endif

#ifndef SKIP_B
    case 12: SetNext(DEV_START_B312);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C3);  break;
#endif

#ifndef SKIP_D
    case 4:  SetNext(DEV_START_D3);  break;
#endif

#ifndef SKIP_F
    case 6:  SetNext(DEV_START_F3);  break;
#endif

#ifndef SKIP_G
    case 9:  SetNext(DEV_START_G3);  break;
#endif

#ifndef SKIP_I
    case 11: SetNext(DEV_START_I3);  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_L
    case 16:
    case 17: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_M
    case 18: SetNext(DEV_START_M3);  break;
#endif

#ifndef SKIP_N
    case 19: SetNext(DEV_START_N3);  break;
#endif

#ifndef SKIP_O
    case 20: SetNext(DEV_START_O3);  break;
#endif

#ifndef SKIP_P
    case 21: SetNext(DEV_START_P3);  break;
#endif

#ifndef SKIP_Q
    case 22: SetNext(DEV_START_Q3);  break;
#endif

#ifndef SKIP_R
    case 23: SetNext(DEV_START_R3);  break;
#endif

#ifndef SKIP_S
    case 24: SetNext(DEV_START_S3);  break;
#endif

#ifndef SKIP_T
    case 25: SetNext(DEV_START_T3);  break;
#endif

#ifndef SKIP_U
    case 26:
    case 28: SetNext(DEV_START_U3);  break;
#endif

#ifndef SKIP_V
    case 27: SetNext(DEV_START_V3);  break;
#endif

#ifndef SKIP_W
    case 29:
    case 30: SetNext(DEV_START_W3);  break;
#endif

#ifndef SKIP_31
    case 31: SetNext(DEV_START_31C);  break;
#endif

#ifndef SKIP_34
    case 34: SetNext(DEV_START_34C);  break;
#endif

#ifndef SKIP_35
    case 35: SetNext(DEV_START_35C);  break;
#endif

#ifndef SKIP_36
    case 36:
    case 37: SetNext(DEV_START_36C);  break;
#endif

#ifndef SKIP_38
    case 38: SetNext(DEV_START_38C);  break;
#endif
  }

  exExtended = EXT_CURRENT_3MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunCurrent(void)
{
  if (boEnblCurrent != true)
    return;
  else if (IsAutoFlowTime())
    return;
  {
    CloseFlow();

    if (GetCurr() == DEV_PAUSE) return;
    if (fConnect == 1) return;

    StartCurrent2();

    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    if (StartCurrent(0) == 0)
    {
      fCurrent = 0;
      Work(); OK();

      wProgram = 0;
      cbShowCurrTime = 2;
    }
  }
}


void    NextCurrent(void)
{
  Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_D
    case 4:  QueryCloseD(0); break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: QueryCloseK();  break;
#endif

#ifndef SKIP_L
    case 16:
    case 17: QueryCloseK();  break;
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

#ifndef SKIP_38
    case 38: Query38_DISC();  break;
#endif
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;

  if (StartCurrent(ibDig+1) == 0) // опрос завершён
  {
    SetCurr(DEV_BEGIN);

    fCurrent = 0;
    StopCurrent2();
    Work(); OK();

    wProgram = 0;
    cbShowCurrTime = 2;

    ibPortPause = 0xFF;

    AfterCurrectPhones2();
  }
}



void    MakeCurrent(void)
{
  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1)
    {
      mpbCurrent2Curr[c/8] |= (0x80 >> c%8);

      if (boMntEscS == true)
      {
        mpdbEsc_S[c] = mpdbValueCntHou[c] * mpdwBase[c];
        mptiEsc_S[c] = *GetCurrTimeDate();
      }

      mpboReadyCan[c] = true;

      mpwTrue[c]++;
      if (mpboBase[c] == false)
      {
        mpboBase[c] = true;

        mpdwBase[c] = mpdwBaseDig[ diPrev.ibLine ];
        mpreBase[c] = 0;
        mptiBase[c] = *GetCurrTimeDate();
        mptiOffs[c] = tiOffs;
      }
      else
      {
        time tiDig = *GetCurrTimeDate();
        time tiAlt = mptiBase[c];

        ulong dwSecond;

        if ((tiAlt.bYear  == tiDig.bYear)  &&
            (tiAlt.bMonth == tiDig.bMonth) &&
            (tiAlt.bDay   == tiDig.bDay))
          dwSecond = 0;
        else
          dwSecond = (ulong)24*3600;

        slong dwImp = mpdwBaseDig[ GetDigitalLine(c) ] - mpdwBase[c];
        mpdwBase[c] = mpdwBaseDig[ GetDigitalLine(c) ];

        dwSecond += GetSecondIndex(tiDig);
        dwSecond -= GetSecondIndex(mptiBase[c]);

        mptiBase[c] = tiDig;
        mptiOffs[c] = tiOffs;

        mptiBaseOK[c] = *GetCurrTimeDate();

        if ((dwSecond > 0) && (dwSecond < 1800))
          mpreBase[c] += (float)180*dwImp/dwSecond;

        dwImp = mpreBase[c];
        mpreBase[c] -= dwImp;

        if (dwImp > 100) mpwMore100[c]++;
        if (dwImp > 1000) mpwMore1000[c]++;
        if (dwImp > 10000) mpwMore10000[c]++;

        if (dwImp > 0xFFFF)
          mpwOverflow[c]++;
        else
        if (dwImp < 0)
          mpwUnderflow[c]++;
        else
        {
          SetImpMnt(1, c, (uint)dwImp);
          MakeSpecCurrent(c, (uint)dwImp);
        }
      }
    }
  }

  NextCurrent();
}



void    ErrorCurrent(void)
{
uchar   ibCan;

  SaveDisplay();

  ShowHi(szWarning);
  Clear();
  sprintf(szLo,"запроса %02X.%02X.%02X",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  DelayMsg();
  LoadDisplay();


  // запрещаем опрашивать другие каналы, принадлежащие текущему счётчику
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    {
      mpboReadyCan[ibCan] = true;

      mptiBaseError[ibCan] = *GetCurrTimeDate();
      mpwFalse[ibCan]++;
    }
  }

  SetCurr(DEV_BEGIN);
  NextCurrent();
}
