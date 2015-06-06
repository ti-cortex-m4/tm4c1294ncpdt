/*------------------------------------------------------------------------------
CURRENT.C

 Расчет трехминутных графиков с цифровых счетчиков
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_extended_1.h"
#include "../../realtime/realtime.h"
#include "../../digitals/digitals.h"
#include "../../time/rtc.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "current.h"



// проверяет типы счетчиков без получасовых графиков
bool    IsSpecCurrent(uchar  i)
{
  if ((i == 12) ||
      (i == 16) ||
      (i == 17) ||
      (i == 18) ||
      (i == 19) ||
      (i == 23)) return(1);

  return(0);
}



void    MakeSpecCurrent(uchar  ibCan, uint  wImp)
{
  double db = 0;

  if (IsSpecCurrent(GetDigitalDevice(ibCan)) == 1)
  {
    // обработка информации по импульсам
    mpwImpHouCan[ibSoftHou][ibCan] += wImp;

    AddCanImpEng(mpimDayCan[ibSoftDay], ibCan, wImp);
    AddCanImpEng(mpimMonCan[ibSoftMon], ibCan, wImp);
    AddCanImpEng(mpimAbsCan,            ibCan,wImp);


    // подготовка информации для Esc V
    if (LoadCntMon(tiCurr.bMonth-1) == false)
      db = 0;
    else
      db = mpdbCntMonCan[ PrevSoftMon() ][ibCan];

    mpdbEsc_V[ibCan] = db;
    mptiEsc_V[ibCan] = *GetCurrTimeDate();


    // подготовка информации для Esc S
    db  = mpdwBase[ibCan] * mpdbValueCntHou[ibCan];
    if (GetDigitalDevice(ibCan) == 19)
      db += mpdbCount[ibCan];

    mpdbEsc_S[ibCan] = db;
    mptiEsc_S[ibCan] = *GetCurrTimeDate();


    // подготовка информации для Esc U
    mptiEsc_U1[ibCan] = tiCurr;
    mptiEsc_U2[ibCan] = *GetCurrTimeDate();
  }
}
