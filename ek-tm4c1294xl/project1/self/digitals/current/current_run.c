/*------------------------------------------------------------------------------
CURRENT_RUN.C


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
#include "../../realtime/realtime.h"
#include "../../sensors/device_p.h"
#include "../../sensors/device_u.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/digitals_pause.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/current/current.h"
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
        (diCurr.bDevice == 22) || (diCurr.bDevice == 26) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24))
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
    case 26: SetNext(DEV_START_U3);  break;
#endif
  }

  exExtended = EXT_CURRENT_3MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunCurrent(void)
{
  if (boEnblCurrent == true)
  {
    CloseFlow();

    if (GetCurr() == DEV_PAUSE) return;
    if (fConnect == 1) return;

    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    if (StartCurrent(0) == 0)
    {
      fCurrent = 0;
      Work(); OK();

      wProgram = 0;
      cbShowCurrentTime = 2;
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
    case 26: QueryCloseU();  break;
#endif
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;

  if (StartCurrent(ibDig+1) == 0) // ����� ��������
  {
    SetCurr(DEV_BEGIN);

    fCurrent = 0;
    Work(); OK();

    wProgram = 0;
    cbShowCurrentTime = 2;

    ibPortPause = 0xFF;
  }
}



void    MakeCurrent(void)
{
uchar   ibCan;

  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    {
      mpbCurrent2Curr[ibCan/8] |= (0x80 >> ibCan%8);

      if (boMntEscS == true)
      {
        mpdbEsc_S[ibCan] = mpdbValueCntHou[ibCan] * mpdwBase[ibCan];
        mptiEsc_S[ibCan] = *GetCurrTimeDate();
      }

      mpboReadyCan[ibCan] = true;

      mpwTrue[ibCan]++;
      if (mpboBase[ibCan] == false)
      {
        mpboBase[ibCan] = true;

        mpdwBase[ibCan] = mpdwBaseDig[ diPrev.ibLine ];
        mpreBase[ibCan] = 0;
        mptiBase[ibCan] = *GetCurrTimeDate();
        mptiOffs[ibCan] = tiOffs;
      }
      else
      {
        time tiDig = *GetCurrTimeDate();
        time tiAlt = mptiBase[ibCan];

        ulong dwSecond;

        if ((tiAlt.bYear  == tiDig.bYear)  &&
            (tiAlt.bMonth == tiDig.bMonth) &&
            (tiAlt.bDay   == tiDig.bDay))
          dwSecond = 0;
        else
          dwSecond = (ulong)24*3600;

        slong dwImp = mpdwBaseDig[ GetDigitalLine(ibCan) ] - mpdwBase[ibCan];
        mpdwBase[ibCan] = mpdwBaseDig[ GetDigitalLine(ibCan) ];

        dwSecond += GetSecondIndex(tiDig);
        dwSecond -= GetSecondIndex(mptiBase[ibCan]);

        mptiBase[ibCan] = tiDig;
        mptiOffs[ibCan] = tiOffs;

        mptiBaseOK[ibCan] = *GetCurrTimeDate();

        if ((dwSecond > 0) && (dwSecond < 1800))
          mpreBase[ibCan] += (float)180*dwImp/dwSecond;

        dwImp = mpreBase[ibCan];
        mpreBase[ibCan] -= dwImp;

        if (dwImp > 100) mpwMore100[ibCan]++;
        if (dwImp > 1000) mpwMore1000[ibCan]++;
        if (dwImp > 10000) mpwMore10000[ibCan]++;

        if (dwImp > 0xFFFF)
          mpwOverflow[ibCan]++;
        else
        if (dwImp < 0)
          mpwUnderflow[ibCan]++;
        else
        {
          LoadImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES);
          mpwImpMntCan[ PrevSoftMnt() ][ibCan] = (uint)dwImp;
          SaveImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES, PrevSoftMnt());

          MakeSpecCurrent(ibCan, (uint)dwImp);
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
  sprintf(szLo,"������� %02X.%02X.%02X",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  DelayMsg();
  LoadDisplay();


  // ��������� ���������� ������ ������, ������������� �������� ��������
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
