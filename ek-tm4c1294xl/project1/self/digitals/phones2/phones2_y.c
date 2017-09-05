/*------------------------------------------------------------------------------
PHONES2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_phones2.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../realtime/realtime.h"
#include "../../energy4.h"
#include "../../serial/ports.h"
#include "../../serial/ports_push.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "../../flash/records.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "phones2_x.h"
#include "phones2.h"



phones2 SafeWritePhones2(uchar  ibPrt, bool  fDebug) {
stream  s;
uint    w;
phones2 f;

  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) {
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mpwMinorInDelay[ibPrt] = w;
  }
  else {
    s = mppoPorts[ibPrt].enStream;
    mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mppoPorts[ibPrt].enStream = s;
    mpwMinorInDelay[ibPrt] = w;
  }

  mpbBuffPhones2[PHONE2_RECORD-1] = f;

  if (f < PHONE2_CODES-1) {
    mpstPhones2[f].cwSelf++;
    mpstPhones2[f].tiSelf = *GetCurrTimeDate();
  }
  else {
    mpstPhones2[PHONE2_CODES-1].cwSelf++;
    mpstPhones2[PHONE2_CODES-1].tiSelf = *GetCurrTimeDate();
  }

  return f;
}


void    RunPhones2(bool  fDebug) {
  if (UsePhones2()) {
    Clear();

    ibPort = bPortPhones2-1;
    diCurr.ibPort = bPortPhones2-1;

    if (SafeWritePhones2(bPortPhones2-1, fDebug) == PH2_OK) {
      if (fDebug == false) cdwPhones25++;
    }
    else
      Error();

    mpSerial[ibPort] = SER_BEGIN;

    Work();
  }
}
