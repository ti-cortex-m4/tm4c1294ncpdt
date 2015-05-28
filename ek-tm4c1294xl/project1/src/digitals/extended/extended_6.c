/*------------------------------------------------------------------------------
EXTENDED_6.C

 �������� ���������
 �� ������ ������� ����� (��� �������� ������) ��� �� ����� ������ (��� ��������� �������, ����� ��������)
 �� ������ �������� ������ (o���� �52 �� 21.11.2009)
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



file const              flExt6Flag = {EXT_6_FLAG, &fExt6Flag, sizeof(bool)};
file const              flCntDayCan6 = {EXT_6_VALUES, &mpCntDayCan6, sizeof(mpCntDayCan6)};



bool SaveCntMonCan6(uchar  ibMonTo)
{
  return SaveBuff(EXT_6_MON_VALUES + ibMonTo*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}


bool LoadCntMonCan6(uchar  ibMonFrom)
{
  return LoadBuff(EXT_6_MON_VALUES + ibMonFrom*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}



void    InitExtended6(void)
{
  LoadFileBoolean(&flExt6Flag, false);
  LoadFile(&flCntDayCan6);
}


void    ResetExtended6(void) 
{ 
  cwDayCan6 = 0;
  cwMonCan6 = 0;

  fExt6Flag = false;
  SaveFile(&flExt6Flag);


  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveCntMonCan6(m);
  }


  memset(&mpCntDayCan6, 0, sizeof(mpCntDayCan6));
  SaveFile(&flCntDayCan6);
}


void    NextDayExtended6(void)
{ 
  cwDayCan6++;

  memset(&mpCntDayCan6, 0, sizeof(mpCntDayCan6));
  SaveFile(&flCntDayCan6);
}


void    NextMonExtended6(void) 
{ 
  cwMonCan6++;

  memset(&mpCntMonCan6, 0, sizeof(mpCntDayCan6));
  SaveCntMonCan6(ibHardMon);
}


void    CloseExtended6(void)
{
  SaveFile(&flCntDayCan6);
  SaveCntMonCan6(ibHardMon);
}



void    MakeExtended6(uchar  ibCan, double  db)
{
  value6 vl;

  vl.bStatus = ST4_OK;
  vl.dbValue = db;
  vl.tiUpdate = *GetCurrTimeDate();
 
  mpCntMonCan6[ibCan] = vl;

  if (mpCntDayCan6[ibCan].bStatus == ST4_NONE)
  {
    mpCntDayCan6[ibCan] = vl;
  }
}




bool    SupportedExtended6(uchar  ibCan)
{
  return ((fExt6Flag == true) && ((GetDigitalDevice(ibCan) == 4) || (GetDigitalDevice(ibCan) == 21)));
}


bool    SupportedExtended6_CurrMon(uchar  ibCan, uchar  ibMon)
{
  return (SupportedExtended6(ibCan) && (ibMon == (*GetCurrTimeDate()).bMonth - 1));
}
