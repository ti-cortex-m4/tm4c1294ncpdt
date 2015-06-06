/*------------------------------------------------------------------------------
REFILL.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../realtime/realtime_spec.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../impulses/energy_spec.h"
#include "../../time/decret.h"
#include "../../flash/records.h"
#include "../../flash/files.h"
#include "refill.h"



// запрет очистки неинициализованных получасовых графиков
bool                    boDsblRefill;

// переменные дл€ заполнени€ пропущенных получасов
static uint             iwBmin, iwBmax;

// переменные дл€ обработки перехода на зимнее врем€
static uchar            bRefillWinter, mpbRefillWinter[10];


file const              flDsblRefill = {DSBL_REFILL, &boDsblRefill, sizeof(bool)};



void    InitRefill(void)
{
  LoadFile(&flDsblRefill);
}


void    ResetRefill(void)
{
	boDsblRefill = false;
  SaveFile(&flDsblRefill);
}


void    StartRefill(void)
{
  iwBmin = 0xFFFF;
  memset(&mpbRefillWinter, 0, sizeof(mpbRefillWinter));
}



void    DoRefill(void)
{
  uint iwB = 0;
  uint iwHou = iwBmin;
  
  while (iwHou != iwBmax) {
    if (fKey == true) { fKey = 0; Beep(); }
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    Clear();
    sprintf(szLo,"обработано: %u",++iwB);

    LoadImpHouSpec(iwHou,1);

    uchar ibCan;
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      if (CompareLines(ibDig,ibCan) == 1) 
        mpwImpHouCanSpec[ibCan] = 0; 
    }

    SaveImpHouSpec(1,iwHou);

    iwHou = (wHOURS+iwHou-1)%wHOURS; 
  }
}



void    MakeRefillWinter(time  ti)
{
  if (IsWinter(ti)) {
    bRefillWinter = ++mpbRefillWinter[ti.bHour*2 + ti.bMinute/30];
  }
}



void    MakeRefill(time  ti)
{
  if (IsWinter(ti) && (bRefillWinter > 1)) return;

  if ((iwBmin != 0xFFFF) && (iwBmin != iwDigHou))
  {
    if ((iwDigHou+1)%wHOURS != iwBmin)
    { 
      iwBmin = (wHOURS+iwBmin-1)%wHOURS; 
      iwBmax = iwDigHou; 

      Clear(); AddDigRecord(EVE_REFILL1);
      DoRefill();
      Clear(); AddDigRecord(EVE_REFILL2);
    }
  }

  iwBmin = iwDigHou;
}



// ошибка: если счетчик ћеркурий-230 запрограммирован без перехода на летнее врем€, а сумматор (в т.ч. старый) с переходом на летнее врем€,
// то при первичном опросе при опроса профил€ за момент перехода все профили сумматора по данному счетчику обнул€ютс€.
