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
#include "../../display/display.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "../../flash/records.h"
#include "../../time/delay.h"
#include "../../kernel/array_mnt.h"
#include "current.h"
#include "current_run.h"
#include "current2.h"



cache const             chEnblCurrent2 = {ENBL_CURRENT2, &fEnblCurrent2, sizeof(bool)};
cache const             chCurrent2Mnt = {CURRENT2_MNT, &mpwCurrent2Mnt, sizeof(mpwCurrent2Mnt)};
cache const             chCurrent2Overflow = {CURRENT2_OVERFLOW, &mpwCurrent2Overflow, sizeof(mpwCurrent2Overflow)};



void    InitCurrent2(void)
{
  LoadCacheBool(&chEnblCurrent2, true);

  LoadCache(&chCurrent2Mnt);
  LoadCache(&chCurrent2Overflow);

  memset(&mpbCurrent2Curr, 0, 8);
  memset(&mpbCurrent2Prev, 0, 8);
  fCurrent2First = true;
}


void    ResetCurrent2(void)
{
  fEnblCurrent2 = true;
  SaveCache(&chEnblCurrent2);

  memset(&mpwCurrent2Mnt, 0, sizeof(mpwCurrent2Mnt));
  SaveCache(&chCurrent2Mnt);

  memset(&mpwCurrent2Overflow, 0, sizeof(mpwCurrent2Overflow));
  SaveCache(&chCurrent2Overflow);
}



void    NextMntCurrent2(void)
{
  if (fEnblCurrent2 == true)
  {
    uchar c;
    for (c=0; c<64; c++)
    {
      if (GetDigitalDevice(c) != 0)
        mpwCurrent2Mnt[c]++;
    }

    SaveCache(&chCurrent2Mnt);
  }
}



void    StartCurrent2(void) 
{
  memset(&mpbCurrent2Curr, 0, 8);
}



void    Current2Disabled(uchar  ibCan, ulong  dwImp)
{
  uint wImp;
  if (dwImp > 0xFFFF)
  { 
    wImp = 0xFFFF;

    mpwCurrent2Overflow[ibCan]++;
    SaveCache(&chCurrent2Overflow);

    AddDigRecord(EVE_CURRENT2_OVERFLOW);
  }
  else
  {
    wImp = (uint)dwImp;
  }

  LoadImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES);
  mpwImpMntCan[ PrevSoftMnt() ][ibCan] = wImp;
  SaveImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES, PrevSoftMnt());

  MakeSpecCurrent(ibCan, (uint)dwImp);
}


void    Current2Enabled(uchar  ibCan, ulong  dwImp)
{
  if (mpwCurrent2Mnt[ibCan] == 1)
  {
    Current2Disabled(ibCan, dwImp);
  }
  else if (mpwCurrent2Mnt[ibCan] > (tiCurr.bMinute%30)/3)
  {
    Current2Disabled(ibCan, dwImp);
    AddDigRecord(EVE_CURRENT2_LIMIT);
  }
  else
  {
    dwRecord = dwImp;
    wRecord = mpwCurrent2Mnt[ibCan];
    AddDigRecord(EVE_CURRENT2_VALUE);

    ulong dw = dwImp;

    uchar i;
    for (i=mpwCurrent2Mnt[ibCan]; i>1; i--) 
    {
      float fl = dw / i;

      LoadImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES);
      mpwImpMntCan[ PrevSoftMnt() ][ibCan] = (uint)fl;
      SaveImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES, PrevSoftMnt());

      dw -= (uint)fl;
    }

    LoadImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES);
    mpwImpMntCan[ PrevSoftMnt() ][ibCan] = (uint)dw;
    SaveImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES, PrevSoftMnt());

    MakeSpecCurrent(ibCan, (uint)dwImp);
  }
}



void    MakeCurrent2(void)
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

        mpreBase[c] += dwImp; // энерги€, а не средн€€ мощность

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
          (fEnblCurrent2 == true ? Current2Enabled(c, dwImp) : Current2Disabled(c, dwImp));
        }
      }

      mpwCurrent2Mnt[c] = 0;
    }
  }

  SaveCache(&chCurrent2Mnt);

  NextCurrent();
}



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
  PushChar(fEnblCurrent2);
  PushIntArray(mpwCurrent2Mnt, bCANALS);
  PushIntArray(mpwCurrent2Overflow, bCANALS);
  Output(1+64*2+64*2);
}
