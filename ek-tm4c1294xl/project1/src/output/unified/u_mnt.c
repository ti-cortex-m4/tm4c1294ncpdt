/*------------------------------------------------------------------------------
U_MNT.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "rtc.h"
#include        "timedate.h"
#include        "queries2.h"
#include        "ports.h"
#include        "engine.h"
#include        "energy.h"
#include        "postinput2.h"



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

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      for (i=bInBuffB; i<bInBuffB+bInBuffD; i++)
      {
        reBuffA = *PGetCanMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibCan-1, 20);
        PushFloat();
      }
    }

    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToMntIndex();
    dwBuffC -= bInBuffB;
    MntIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, &tiAlt);
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

    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      for (i=bInBuffB; i<bInBuffB+bInBuffD; i++)
      {
        reBuffA = *PGetGrpMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibGrp-1, 20);
        PushFloat();
      }
    }

    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToMntIndex();
    dwBuffC -= bInBuffB;
    MntIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuffD*bInBuff9, 0, &tiAlt);
  }
}

#endif
*/
