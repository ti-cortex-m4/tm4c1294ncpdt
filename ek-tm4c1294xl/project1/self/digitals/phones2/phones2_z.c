/*------------------------------------------------------------------------------
PHONES2_FACADE*C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_phones2.h"
#include "../../keyboard/keyboard.h"
#include "../../display/display.h"
#include "../../serial/ports.h"
#include "../../realtime/realtime.h"
#include "../../digitals/digitals_status.h"
#include "../../time/delay.h"
#include "../../flash/records.h"
#include "../../energy4.h"
#include "phones2.h"
#include "phones2_z.h"



//                                         0123456789ABCDEF
static char const       szPhonesRun2[]    = "СМС-контроль    ",
                        szNoExcess[]      = "нет превышения !",
                        szNoPeak[]        = "непиковые зоны !";



void    TestPhones2(void) {
  AddPh2Record(EVE_PH2_DEBUG);
  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

  RunPhones2(false);

  AddPh2Record(EVE_PH2_FINISH);

  SetCurr(DEV_BEGIN);
  ibPortPause = 0xFF;
}



static void MakePhones2(void) {
  if (UsePhones2() && (enGlobal != GLB_PROGRAM))  {

    cdwPhones20++;
    if ((mpibPowCurrTariff[ GetCurrHouIndex() ] == 2) ||
        (mpibPowCurrTariff[ GetCurrHouIndex() ] == 3))  {

      cdwPhones21++;
      reCurrPhones2 = GetPowGrpHouCurr(0,2);
      if (reCurrPhones2 > reMaxxPhones2) {

        cdwPhones23++;
        AddPh2Record(EVE_PH2_START);
        memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

        RunPhones2(false);

        AddPh2Record(EVE_PH2_FINISH);

        Work(); OK();

        wProgram = 0;
        cbShowCurrTime = 2;

        SetCurr(DEV_BEGIN);
        ibPortPause = 0xFF;
      }
      else {
        cdwPhones24++;
        if (boShowMessages == true) {
          ShowHi(szPhonesRun2); ShowLo(szNoExcess);
          DelayMsg();
          Work(); OK();
        }
      }
    }
    else {
      cdwPhones22++;
      if (boShowMessages == true) {
        ShowHi(szPhonesRun2); ShowLo(szNoPeak);
        DelayMsg();
        Work(); OK();
      }
    }
  }
}


void   EverySecondPhones2(void) {
  if (bDelayPhone2 > 0) {
    if (bDelayPhone2-- == 1) MakePhones2();
  }
}


void    AfterCurrectPhones2(void) {
  bDelayPhone2 = 3;
}
