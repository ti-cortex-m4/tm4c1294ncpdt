/*------------------------------------------------------------------------------
PHONES2_Y!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../time/rtc.h"
#include "../../serial/ports.h"
#include "phones2_x.h"
#include "phones2.h"
#include "phones2_y.h"



phones2 SafeWritePhones2(uchar  ibPrt, bool  fDebug) {
phones2 f;

  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) {
    uint w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;

    f = WritePhones2(fDebug);

    mpwMinorInDelay[ibPrt] = w;
  }
  else {
    stream s = mppoPorts[ibPrt].enStream;
    mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
    uint w = mpwMinorInDelay[ibPrt];
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
    else {
      Error();
    }

    mpSerial[ibPort] = SER_BEGIN;

    Work();
  }
}
