/*------------------------------------------------------------------------------
UNI_HHR,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_energy_spec.h"
#include "../../include/states.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../realtime/realtime.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../special/recalc_def.h"
#include "../../groups.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "response_uni.h"
#include "u_def.h"
#include "uni_hhr.h"



void    GetPowCanHouUni(void)
{
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
    bool fDef = 0;
    uint wSize = 0;

    uint iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;

    uchar i;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      uchar c;
      for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
      {      
        fDef |= GetDefCan(c-1);
        InitPush(6 + 4*bInBuffD*(c-bInBuff7) + i*4);

        if (mpwImpHouCan[ PrevSoftHou() ][c-1] == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c-1, 2));
        }

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    ulong dw = DateToHouIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = HouIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((fDef == 0) ? bUNI_OK : bUNI_DEFECT), ti);
  }
}



void    GetPowGrpHouUni(void)
{
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
    bool fDef = 0;
    uint wSize = 0;

    uint iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;

    uchar i;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      uchar g;
      for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
      {      
        fDef |= GetDefCan(g-1);
        InitPush(6 + 4*bInBuffD*(g-bInBuff7) + i*4);

        PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g-1, 2));

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    ulong dw = DateToHouIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = HouIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((fDef == 0) ? bUNI_OK : bUNI_DEFECT), ti);
  }
}



void    GetPowCanHou48Uni(void) 
{
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
    bool fDef = 0;
    uint wSize = 0;

    uint iwHou = GetDayHouIndex(bInBuffB);

    uchar i;
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      uchar c;
      for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
      {      
        fDef |= GetDefCan(c-1);
        InitPush(6 + 4*48*(c-bInBuff7) + i*4);

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else if (mpwImpHouCan[ PrevSoftHou() ][c-1] == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c-1, 2));
        }

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)4*48*bInBuff9, ((fDef == 0) ? bUNI_OK : bUNI_DEFECT), ti);
  }
}



void    GetPowGrpHou48Uni(void) 
{
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
    bool fDef = 0;
    uint wSize = 0;

    uint iwHou = GetDayHouIndex(bInBuffB);

    uchar i;
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      uchar g;
      for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
      {      
        fDef |= GetDefCan(g-1);
        InitPush(6 + 4*48*(g-bInBuff7) + i*4);

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else 
        {
          PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g-1, 2));
        }

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)4*48*bInBuff9, ((fDef == 0) ? bUNI_OK : bUNI_DEFECT), ti);
  }
}
