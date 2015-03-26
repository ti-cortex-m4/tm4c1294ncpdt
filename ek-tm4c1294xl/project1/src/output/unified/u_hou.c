/*------------------------------------------------------------------------------
U_HOU.C


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
#include        "general.h"
#include        "nexttime.h"
#include        "postinput2.h"



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
    fAlt = 0;
    wBuffD = 0;

    iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
      {      
        fAlt |= GetDefCan(ibCan-1);
        InitPush2((uint)(6 + 4*bInBuffD*(ibCan-bInBuff7) + i*4));

        if (*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], ibCan-1) == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          reBuffA = *PGetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibCan-1, 2);
          PushReal();
        }

        wBuffD += sizeof(real);
        if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToHouIndex();
    dwBuffC -= bInBuffB;
    HouIndexToDate(dwBuffC);

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
    fAlt = 0;
    wBuffD = 0;

    iwHou = (wHOURS+iwHardHou-bInBuffB) % wHOURS;
    for (i=0; i<bInBuffD; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
      {      
        fAlt |= GetDefCan(ibGrp-1);
        InitPush2((uint)(6 + 4*bInBuffD*(ibGrp-bInBuff7) + i*4));

        reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp-1, 2);
        PushReal();

        wBuffD += sizeof(real);
        if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (iwHou > 0) iwHou--; else iwHou = wHOURS-1;
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToHouIndex();
    dwBuffC -= bInBuffB;
    HouIndexToDate(dwBuffC);

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
    fAlt = 0;
    wBuffD = 0;

    iwHou = PrevDayIndex(bInBuffB);
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
      {      
        fAlt |= GetDefCan(ibCan-1);
        InitPush2((uint)(6 + 4*48*(ibCan-bInBuff7) + i*4));

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else 
        if (*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], ibCan-1) == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          reBuffA = *PGetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibCan-1, 2);
          PushReal();
        }

        wBuffD += sizeof(real);
        if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

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
    fAlt = 0;
    wBuffD = 0;

    iwHou = PrevDayIndex(bInBuffB);
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
      {      
        fAlt |= GetDefCan(ibGrp-1);
        InitPush2((uint)(6 + 4*48*(ibGrp-bInBuff7) + i*4));

        if ((bInBuffB == 0) && (i > GetCurrHouIndex()))
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else 
        {
          reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp-1, 2);
          PushReal();
        }

        wBuffD += sizeof(real);
        if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)4*48*bInBuff9, ((fAlt == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}

#endif
*/
