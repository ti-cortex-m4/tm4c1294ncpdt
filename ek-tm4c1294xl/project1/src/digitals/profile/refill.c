/*------------------------------------------------------------------------------
ESSENTIAL2.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../display/display.h"
#include        "../../keyboard/keyboard.h"
#include        "../../flash/files.h"



file const              flDsblRefill = {FLS_DSBL_REFILL, &boDsblRefill, sizeof(boolean)};



void    StartRefill(void)
{
  iwBmin = 0xFFFF;
  memset(&mpbRefillWinter, boFalse, sizeof(mpbRefillWinter));
}



void    DoRefill(void)
{
  iwB = 0;
  iwHou = iwBmin; 
  
  while (iwHou != iwBmax) {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    sprintf(szLo,"обработано: %u  ",++iwB);
    LoadImpHouSpec(iwHou,1);

    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      if (CompareLines(ibDig,ibCan) == 1) 
        mpwImpHouCanSpec[ibCan] = 0; 
    }

    SaveImpHouSpec(1,iwHou);

    iwHou = (wHOURS+iwHou-1)%wHOURS; 
  }
}



void    MakeRefillWinter(void)
{
  if (IsWinterAlt()) {
    bRefillWinter = ++mpbRefillWinter[tiAlt.bHour*2 + tiAlt.bMinute/30]; 
  }
}



void    MakeRefill(void)
{
  if (IsWinterAlt() && (bRefillWinter > 1)) return;

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
