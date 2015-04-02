/*------------------------------------------------------------------------------
U_HOU.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../../memory/mem_energy_spec.h"
#include        "../../include/states.h"
#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
#include        "../../time/rtc.h"
#include        "../../time/timedate.h"
#include        "../../time/calendar.h"
#include        "../../special/recalc_def.h"
#include        "../../groups.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "response_uni.h"
#include        "u_def.h"
#include        "u_hou.h"



#ifndef MODBUS

void    GetPowCanHouUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB+bInBuffD-1 > wHOURS)
    Result2(bUNI_BADDATA);
  else
  {
    bool fAlt = 0;
    uint wSize = 0;

    iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
      {      
        fAlt |= GetDefCan(ibCan-1);
        InitPush((uint)(6 + 4*bInBuffD*(ibCan-bInBuff7) + i*4));

        if (GetCanInt(mpwImpHouCan[ PrevSoftHou() ], ibCan-1) == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibCan-1, 2));
        }

        wSize += sizeof(real);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    ulong dw = DateToHouIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    HouIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((fAlt == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}



void    GetPowGrpHouUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB+bInBuffD-1 > wHOURS)
    Result2(bUNI_BADDATA);
  else
  {
    bool fAlt = 0;
    uint wSize = 0;

    iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
      {      
        fAlt |= GetDefCan(ibGrp-1);
        InitPush((uint)(6 + 4*bInBuffD*(ibGrp-bInBuff7) + i*4));

        PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp-1, 2));

        wSize += sizeof(real);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    ulong dw = DateToHouIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    HouIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((fAlt == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}



void    GetPowCanHou48Uni(void) 
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= wHOURS/48)
    Result2(bUNI_BADDATA);
  else
  {
    bool fAlt = 0;
    uint wSize = 0;

    iwHou = GetDayHouIndex(bInBuffB);
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
      {      
        fAlt |= GetDefCan(ibCan-1);
        InitPush((uint)(6 + 4*48*(ibCan-bInBuff7) + i*4));

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else 
        if (GetCanInt(mpwImpHouCan[ PrevSoftHou() ], ibCan-1) == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibCan-1, 2));
        }

        wSize += sizeof(real);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    DayIndexToDate(dw);

    Output2_Code((uint)4*48*bInBuff9, ((fAlt == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}



void    GetPowGrpHou48Uni(void) 
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= wHOURS/48)
    Result2(bUNI_BADDATA);
  else
  {
    bool fAlt = 0;
    uint wSize = 0;

    iwHou = GetDayHouIndex(bInBuffB);
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
      {      
        fAlt |= GetDefCan(ibGrp-1);
        InitPush((uint)(6 + 4*48*(ibGrp-bInBuff7) + i*4));

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else 
        {
          PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp-1, 2));
        }

        wSize += sizeof(real);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    DayIndexToDate(dw);

    Output2_Code((uint)4*48*bInBuff9, ((fAlt == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}

#endif
