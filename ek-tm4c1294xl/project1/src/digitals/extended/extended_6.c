/*------------------------------------------------------------------------------
EXTENDED_6.C

 «начени€ счетчиков на конец мес€цев из буфера при€мого опроса (oтчет є52 от 21.11.2009)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../digitals/digitals.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../console.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_6.h"



//                                         0123456789ABCDEF
static char const       szNone[]        = "*    пусто      ";


file const              flExt6Flag = {EXT_6_FLAG, &boExt6Flag, sizeof(boolean)};
file const              flCntCan6 = {EXT_6_VALUES, &mpCntCan6, sizeof(mpCntCan6)};



static boolean SaveCntMonCan6(uchar  ibMonTo)
{
  return SaveBuff(EXT_6_MON_VALUES + ibMonTo*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}


static boolean LoadCntMonCan6(uchar  ibMonFrom)
{
  return LoadBuff(EXT_6_MON_VALUES + ibMonFrom*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}



void    InitExtended6(void)
{
  LoadFileBoolean(&flExt6Flag, FALSE);
  LoadFile(&flCntCan6);
}


void    ResetExtended6(void) 
{ 
  cwDayCan6 = 0;
  cwMonCan6 = 0;

  boExt6Flag = FALSE;
  SaveFile(&flExt6Flag);


  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveCntMonCan6(m);
  }


  memset(&mpCntCan6, 0, sizeof(mpCntCan6));
  SaveFile(&flCntCan6);
}


void    NextDayExtended6(void)
{ 
  cwDayCan6++;

  memset(&mpCntCan6, 0, sizeof(mpCntCan6));
  SaveFile(&flCntCan6);
}


void    NextMonExtended6(void) 
{ 
  cwMonCan6++;

  memset(&mpCntMonCan6, 0, sizeof(mpCntCan6));
  SaveCntMonCan6(ibHardMon);
}


void    CloseExtended6(void)
{
  SaveFile(&flCntCan6);
  SaveCntMonCan6(ibHardMon);
}



void    MakeExtended6(uchar  ibCan, real  re)
{
  value6 va;
  va.bSelf = ST4_OK;
  va.reSelf = re;
  va.tiUpdate = *GetCurrTimeDate();
 
  mpCntMonCan6[ibCan] = va;

  if (mpCntCan6[ibCan].bSelf == ST4_NONE)
  {
    mpCntCan6[ibCan] = va;
  }
}



void    OutExtended6(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadCntMonCan6(InBuff(6));

    InitPushPtr();            
    PushInt(cwDayCan6);
    PushInt(cwMonCan6);
    uint wSize = 2+2;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        if (GetDigitalDevice(c) == 0)
        {
          value6 va;
          va.bSelf = ST4_OK;
          va.reSelf = mpreCntMonCan[ PrevSoftMon() ][c];
          va.tiUpdate = tiZero;
          Push(&va, sizeof(value6));
        }
        else
        {
          if (InBuff(6) == (*GetCurrTimeDate()).bMonth - 1)
            Push(&mpCntCan6[c], sizeof(value6));
          else 
            Push(&mpCntMonCan6[c], sizeof(value6));
        }

        wSize += sizeof(value6);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    ShowTimeDate6(time  ti)
{
  sprintf(szLo,"%02u:%02u %02u.%02u.%02u",
               ti.bHour,
               ti.bMinute,
               ti.bDay,
               ti.bMonth,
               ti.bYear);
}


void    ShowCntMonCan6(uchar  ibCan, uchar  ibMon)
{
value6 vl;

  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    vl.bSelf = ST4_OK;
    vl.reSelf = mpreCntMonCan[ PrevSoftMon() ][ibCan];
    vl.tiUpdate = tiZero;
  }
  else
  {
    LoadCntMonCan6(ibMon);

    if (ibMon == (*GetCurrTimeDate()).bMonth - 1)
      vl = mpCntCan6[ibCan];
    else 
      vl = mpCntMonCan6[ibCan];
  }

  reBuffA = vl.reSelf;
  tiAlt = vl.tiUpdate;

  switch (vl.bSelf)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   (ibZ == 0) ? ShowFloat(reBuffA) : ShowTimeDate6(tiAlt); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bSelf); break;
  }  
}


bool    CheckDirectCnt1(uchar  ibCan)
{
  return (((boExt6Flag == TRUE) && (GetDigitalDevice(ibCan) == 4)) ||
                                   (GetDigitalDevice(ibCan) == 21));
}


bool    CheckDirectCnt2(uchar  ibCan, uchar  ibMon)
{
  return (CheckDirectCnt1(ibCan) && (ibMon == (*GetCurrTimeDate()).bMonth - 1));
}


void    ShowDirectCnt(uchar  ibCan)
{
  value6 vl = mpCntCan6[ibCan];

  reBuffA = vl.reSelf;
  tiAlt = vl.tiUpdate;

  switch (vl.bSelf)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   ShowFloat(reBuffA); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bSelf); break;
  }  
}


void    LoadDirectCntReal(uchar  ibCan)
{
  value6 vl = mpCntCan6[ibCan];
  reBuffA = vl.reSelf;
}


void    LoadDirectCntTime(uchar  ibCan)
{
  value6 vl = mpCntCan6[ibCan];
  tiAlt = vl.tiUpdate;
}
