/*------------------------------------------------------------------------------
CURRENT2.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_extended_1.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "../../flash/records.h"
#include "current.h"
#include "current_run.h"
#include "current2.h"



void    InitCurrent2(void)
{
  memset(&mpbCurrent2Curr, 0, 8);
  memset(&mpbCurrent2Prev, 0, 8);
  fCurrent2First = true;
}

/*
void    ResetCurrent2(void)
{
  memset(&mpwCurrent2Mnt, 0, sizeof(mpwCurrent2Mnt));
  memset(&mpwCurrent2Overflow, 0, sizeof(mpwCurrent2Overflow));
  fCurrent2Enbl = true;
}
*/


void    NextMntCurrent2(void)
{
  uchar c;
  for (c=0; c<64; c++)
  {
    if (GetDigitalDevice(c) != 0)
      mpwCurrent2Mnt[c]++;
  }
}



void    StartCurrent2(void) 
{
  memset(&mpbCurrent2Curr, 0, 8);
}


/*
void    Current2Disabled(uchar  ibCan)
{
  uint wImp;

  if (dwUpdate > 0xFFFF)
  { 
    wImp = 0xFFFF;
    mpwCurrent2Overflow[ibCan]++;
    AddDigRecord(EVE_CURRENT2_OVERFLOW);
  }
  else
    wImp = (uint)dwUpdate;

  mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = wImp;
  MakeSpecCurrent();
}


void    Current2Enabled(uchar  ibCan)
{
uchar i;

  if (mpwCurrent2Mnt[ibCan] == 1)
  {
    Current2Disabled(ibCan);
  }
  else if (mpwCurrent2Mnt[ibCan] > (tiCurr.bMinute%30)/3)
  {
    Current2Disabled(ibCan);
    AddDigRecord(EVE_CURRENT2_LIMIT);
  }
  else
  {
    dwFloat = dwUpdate;
    AddDigRecord(EVE_CURRENT2_VALUE);

    for (i=mpwCurrent2Mnt[ibCan]; i>1; i--) 
    {
      reBuffA = dwFloat / i; 
      mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ][ibCan] = (uint)reBuffA;
      dwFloat -= (uint)reBuffA;
    }

    mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = (uint)dwFloat;
    MakeSpecCurrent();
  }
}



void    MakeCurrent2(void)
{
  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    {
      mpbCurrent2Curr[ibCan/8] |= (0x80 >> ibCan%8);

      if (boMntEscS == true)
      {
        mpreEsc_S[ibCan] = mpreValueCntHou[ibCan] * mpdwBase[ibCan];
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
        tiDig = *GetCurrTimeDate();
        tiAlt = mptiBase[ibCan];

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

        mpreBase[ibCan] += dwImp;            // обеспечиваем измерение энергии, а не средней мощности

        dwImp = mpreBase[ibCan];
        mpreBase[ibCan] -= dwImp;

        if (dwImp > 100) mpwMore100[ibCan]++;
        if (dwImp > 1000) mpwMore1000[ibCan]++;
        if (dwImp > 10000) mpwMore10000[ibCan]++;

        if (dwImp > 0xFFFF)                  // переполнение
          mpwOverflow[ibCan]++;
        else
        if (dwImp < 0)                       // заём
          mpwUnderflow[ibCan]++;
        else
        {
          (fCurrent2Enbl == true ? Current2Enabled() : Current2Disabled());
        }
      }

      mpwCurrent2Mnt[ibCan] = 0;
    }
  }

  NextCurrent();
}
*/


static bool Currect2First(void)
{
  uchar c;
  for (c=0; c<64; c++)
  {
    if ((mpbCurrent2Curr[c/8] & (0x80 >> c%8)) == 0)
      return 0;
  }

  return 1;
}


static bool Currect2Next(void)
{
  uchar i;
  for (i=0; i<8; i++)
  {
    if (mpbCurrent2Curr[i] != mpbCurrent2Prev[i])
      return 0;
  }

  return 1;
}


static void Currect2Record(void)
{
  memset(&mpbCurrent2Buff, 0, sizeof(mpbCurrent2Buff));

  uchar c;
  for (c=0; c<64; c++)
  {
    if (GetDigitalDevice(c) != 0)
      if ((mpbCurrent2Curr[c/8] & (0x80 >> c%8)) == 0)
        mpbCurrent2Buff[c/8] |= (0x80 >> c%8);
  }

  AddDigRecord(EVE_CURRENT2_CANALS);
}


void    StopCurrent2(void) 
{
  if (fCurrent2First == true)
  {
    if (Currect2First() == 0) Currect2Record();
  }
  else
  {
    if (Currect2Next() == 0) Currect2Record();
  }

  fCurrent2First = false;
  memcpy(&mpbCurrent2Prev, &mpbCurrent2Curr, 8);
}



void    OutCurrent2(void)
{
  InitPushCRC();
  PushChar(fCurrent2Enbl);
  Push(&mpwCurrent2Mnt, sizeof(mpwCurrent2Mnt));
  Push(&mpwCurrent2Overflow, sizeof(mpwCurrent2Overflow));
  Output(1+64*2+64*2);
}
