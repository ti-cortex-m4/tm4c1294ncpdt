/*------------------------------------------------------------------------------
UNI_MNT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../realtime/realtime.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../energy.h"
#include "../../kernel/array_mnt.h"
#include "response_uni.h"
#include "uni_mnt.h"



void    GetPowCanMntUni(void)
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB+bInBuffD-1 > bMINUTES)
    Result2(bUNI_BADDATA);
  else
  {
    uint wSize = 0;

    uchar ibMnt = (bMINUTES+iwHardMnt-bInBuffB) % bMINUTES;

    uchar i;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpMnt(ibMnt);

      uchar c;
      for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
      {
        InitPush(6 + 4*bInBuffD*(c-bInBuff7) + i*4);

        PushFloat(GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], c-1, 20));

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (ibMnt > 0) ibMnt--; else ibMnt = bMINUTES-1;
    }

    ulong dw = DateToMntIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MntIndexToDate(dw);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, ti);
  }
}



void    GetPowGrpMntUni(void)
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB+bInBuffD-1 > bMINUTES)
    Result2(bUNI_BADDATA);
  else
  {
    uint wSize = 0;

    uchar ibMnt = (bMINUTES+iwHardMnt-bInBuffB) % bMINUTES;

    uchar i;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpMnt(ibMnt);

      uchar g;
      for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
      {
        InitPush(6 + 4*bInBuffD*(g-bInBuff7) + i*4);

        PushFloat(GetGrpMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], g-1, 20));

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (ibMnt > 0) ibMnt--; else ibMnt = bMINUTES-1;
    }

    ulong dw = DateToMntIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MntIndexToDate(dw);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, ti);
  }
}
