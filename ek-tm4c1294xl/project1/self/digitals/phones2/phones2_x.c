/*------------------------------------------------------------------------------
PHONES2*C


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
#include "phones2_serial.h"
#include "phones2_modem.h"
#include "phones2.h"




//                                         0123456789ABCDEF
static char const       szPhonesRun2[]    = "СМС-контроль    ",
                        szPhonesMode21[]  = " настройки 1... ",
                        szPhonesMode22[]  = " настройки 2... ",
                        szPhonesMode23[]  = " настройки 3... ";



phones2 WritePhones2(bool  fDebug) {
uchar i;

  ShowHi(szPhonesRun2);
  QueryMessage0();

  ShowLo(szPhonesMode21);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryModemBaud(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
  }

  if (i == MaxRepeatsFixed()) ;


  ShowLo(szPhonesMode22);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryModemCommon(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1u", i+1);
  }

  if (i == MaxRepeatsFixed())
    return PH2_MODEMCOMMON;


  ShowLo(szPhonesMode23);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryMessageMode();

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1u", i+1);
  }

  if (i == MaxRepeatsFixed())
    return PH2_MESSAGEMODE;


  uchar ibCan;
  for (ibCan=0; ibCan<bPHONES2; ibCan++) {

    line phT = mpphPhones2[ibCan];
    if ((phT.szLine[0] == '0') && (phT.szLine[1] == 0)) continue;

    mpbBuffPhones2[ibCan] = ibCan+1;

    for (i=0; i<MaxRepeatsFixed(); i++) {
      DelayOff();
      QueryMessage1(ibCan);

      if (Phones2Input0() == SER_GOODCHECK) break;
      if (fKey == 1) return PH2_KEYBREAK;
      sprintf(szLo+15, "%1u", i+1);
    }

    if (i == MaxRepeatsFixed())
      return PH2_MESSAGE1;

    DelayOff();
    QueryMessage2(fDebug);

    if (Phones2Input1() == SER_GOODCHECK) ;

    Clear();
    if (Phones2Answer()) {
      (Phones2Result() == 0x30) ? OK() : sprintf(szLo+3, "ошибка: %c", Phones2Result()); // нужно обрабатывать ошибку
    }
    else Error(); // нужно обрабатывать ошибку
    DelayMsg();
  }


  return PH2_OK;
}


