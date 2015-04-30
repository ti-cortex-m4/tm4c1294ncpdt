/*------------------------------------------------------------------------------
U_MNT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../../include/states.h"
#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
#include        "../../time/rtc.h"
#include        "../../time/timedate.h"
#include        "../../time/calendar.h"
#include        "../../energy.h"
#include        "response_uni.h"
#include        "u_mnt.h"



#ifndef MODBUS

void    GetPowCanMntUni(void) 
{
uchar   i;

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
    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      for (i=bInBuffB; i<bInBuffB+bInBuffD; i++)
      {
        PushFloat(GetCanMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], c-1, 20));
      }
    }

    ulong dw = DateToMntIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MntIndexToDate(dw);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, ti);
  }
}



void    GetPowGrpMntUni(void) 
{
uchar   i;

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
    InitPushUni();

    uchar g;
    for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
    {
      for (i=bInBuffB; i<bInBuffB+bInBuffD; i++)
      {
        PushFloat(GetGrpMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], g-1, 20));
      }
    }

    ulong dw = DateToMntIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MntIndexToDate(dw);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, ti);
  }
}

#endif
