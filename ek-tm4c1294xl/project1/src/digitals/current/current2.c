/*------------------------------------------------------------------------------
CURRENT2.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_factors.h"
#include        "../../memory/mem_energy.h"
#include        "../../memory/mem_current.h"
#include        "../../memory/mem_extended_1.h"
#include        "../../realtime/realtime.h"
#include        "../../digitals/digitals.h"
#include        "../../time/rtc.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "current.h"



void    ResetCurrent2(void)
{
  memset(&mpwCurrent2Mnt, 0, sizeof(mpwCurrent2Mnt));
  memset(&mpwCurrent2Overflow, 0, sizeof(mpwCurrent2Overflow));
  boCurrent2Enable = TRUE;
}


void    NextMntCurrent2(void)
{
uchar   i;

  for (i=0; i<64; i++) 
    if (GetDigitalDevice(i) != 0)
      mpwCurrent2Mnt[i]++;
}



void    InitCurrent2(void) 
{
  memset(&mpbCurrent2Curr, 0, 8);
  memset(&mpbCurrent2Prev, 0, 8);
  mpboCurrent2 = TRUE;
}



void    StartCurrent2(void) 
{
  memset(&mpbCurrent2Curr, 0, 8);
}



void    Current2Disabled()
{
  if (dwUpdate > 0xFFFF)
  { 
    wBuffD = 0xFFFF;
    mpwCurrent2Overflow[ibCan]++;
    AddDigRecord(EVE_CURRENT2_OVERFLOW);
  }
  else
    wBuffD = (uint)dwUpdate;

  mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = wBuffD;
  MakeSpecCurrent();
}


void    Current2Enabled()
{
uchar i;

  if (mpwCurrent2Mnt[ibCan] == 1)
  {
    Current2Disabled();
  }
  else if (mpwCurrent2Mnt[ibCan] > (tiCurr.bMinute%30)/3)
  {
    Current2Disabled();
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
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpbCurrent2Curr[ibCan/8] |= (0x80 >> ibCan%8);

      if (boMntEscS == TRUE)
      {
        mpreEsc_S[ibCan] = mpreValueCntHou[ibCan] * mpdwBase[ibCan];
        mptiEsc_S[ibCan] = *PGetCurrTimeDate();
      }

      mpboReadyCan[ibCan] = TRUE;

      mpwTrue[ibCan]++;
      if (mpboBase[ibCan] == boFalse)
      {
        mpboBase[ibCan] = TRUE;

        mpdwBase[ibCan] = mpdwBaseDig[ diPrev.ibLine ];
        mpreBase[ibCan] = 0;
        mptiBase[ibCan] = *PGetCurrTimeDate();
        mptiOffs[ibCan] = tiOffs;
      }
      else
      {
        tiDig = *PGetCurrTimeDate();      
        tiAlt = mptiBase[ibCan];

        if (CompareAltDig(0x07) == 1)           // сравниваем: день, мес€ц, год
          dwBuffC = 0;
        else
          dwBuffC = (ulong)24*3600;

        dwUpdate = mpdwBaseDig[ GetDigitalLine(ibCan) ] - mpdwBase[ibCan];
        mpdwBase[ibCan] = mpdwBaseDig[ GetDigitalLine(ibCan) ];

        tiAlt = tiDig;
        dwBuffC += GetSecondIndex();
        tiAlt = mptiBase[ibCan];
        dwBuffC -= GetSecondIndex();

        mptiBase[ibCan] = tiDig;
        mptiOffs[ibCan] = tiOffs;

        mptiBaseOK[ibCan] = *PGetCurrTimeDate();

        mpreBase[ibCan] += dwUpdate;            // обеспециваем измерение энергии, а не средней мощности

        dwUpdate = mpreBase[ibCan];
        mpreBase[ibCan] -= dwUpdate;

        if (dwUpdate > 100) mpwMore100[ibCan]++;
        if (dwUpdate > 1000) mpwMore1000[ibCan]++;
        if (dwUpdate > 10000) mpwMore10000[ibCan]++;

        if (dwUpdate > 0xFFFF)                  // переполнение
          mpwMore[ibCan]++;
        else
        if (dwUpdate < 0)                       // заЄм
          mpwLess[ibCan]++;
        else
        {
          (boCurrent2Enable == TRUE ? Current2Enabled() : Current2Disabled());
        }
      }

      mpwCurrent2Mnt[ibCan] = 0;
    }
  }

  NextCurrent();
}



bit     Currect2First()
{
uchar i;

  for (i=0; i<64; i++) 
    if ((mpbCurrent2Curr[i/8] & (0x80 >> i%8)) == 0)
      return 0;

  return 1;
}


bit     Currect2Next()
{
uchar i;

  for (i=0; i<8; i++) 
    if (mpbCurrent2Curr[i] != mpbCurrent2Prev[i])
      return 0;

  return 1;
}


void    Currect2Record(void) 
{
uchar i;

  memset(&mpbCurrent2Buff, 0, sizeof(mpbCurrent2Buff));

  for (i=0; i<64; i++) 
    if (GetDigitalDevice(i) != 0)
      if ((mpbCurrent2Curr[i/8] & (0x80 >> i%8)) == 0)
        mpbCurrent2Buff[i/8] |= (0x80 >> i%8);

  AddDigRecord(EVE_CURRENT2_CANALS);
}


void    StopCurrent2(void) 
{
  if (mpboCurrent2 == TRUE )
  {
    if (Currect2First() == 0) Currect2Record();
  }
  else
  {
    if (Currect2Next() == 0) Currect2Record();
  }

  mpboCurrent2 = boFalse;
  memcpy(&mpbCurrent2Prev, &mpbCurrent2Curr, 8);
}
