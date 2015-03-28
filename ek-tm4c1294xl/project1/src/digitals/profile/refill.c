/*------------------------------------------------------------------------------
REFILL.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_energy_spec.h"
#include        "../../display/display.h"
#include        "../../keyboard/keyboard.h"
#include        "../../digitals/digitals.h"
#include        "../../devices/devices.h"
#include        "../../impulses/energy_spec.h"
#include        "../../time/decret.h"
#include        "../../flash/records.h"
#include        "../../flash/files.h"
#include        "refill.h"



// запрет очистки неинициализованных получасовых графиков
boolean                 boDsblRefill;

// переменные для заполнения пропущенных получасов
static uint             iwBmin, iwBmax;

// переменные для обработки перехода на зимнее время
static uchar            bRefillWinter, mpbRefillWinter[10];


file const              flDsblRefill = {FLS_DSBL_REFILL, &boDsblRefill, sizeof(boolean)};



void    InitRefill(void)
{
  LoadFile(&flDsblRefill);
}


void    ResetRefill(void)
{
	boDsblRefill = FALSE;
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
    if (fKey == 1) { fKey = 0; Beep(); }
    //TODO if ((iwHou % 0x10) == 0) NexttimeMnt();

    sprintf(szLo,"обработано: %u  ",++iwB);
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



void    MakeRefillWinter(time  *pti)
{
  if (IsWinter(pti)) {
    bRefillWinter = ++mpbRefillWinter[pti->bHour*2 + pti->bMinute/30];
  }
}



void    MakeRefill(time  *pti)
{
  if (IsWinter(pti) && (bRefillWinter > 1)) return;

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
