/*------------------------------------------------------------------------------
PHONES2_X!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "../../digitals/max_repeats.h"
#include "phones2_serial.h"
#include "phones2_modem.h"
#include "phones2.h"



//                                         0123456789ABCDEF
static char const       szPhonesRun2[]    = "СМС-контроль    ",
                        szPhonesMode21[]  = " настройки 1... ",
                        szPhonesMode22[]  = " настройки 2... ",
                        szPhonesMode23[]  = " настройки 3... ";



phones2 WritePhones2(bool  fDebug) {
  ShowHi(szPhonesRun2);
  QueryMessage0();

  ShowLo(szPhonesMode21);

  uchar i;
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


  uchar p;
  for (p=0; p<bPHONES2; p++) {

    line ph = mpphPhones2[p];
    if ((ph.szLine[0] == '0') && (ph.szLine[1] == 0)) continue;

    mpbBuffPhones2[p] = p+1;

    for (i=0; i<MaxRepeatsFixed(); i++) {
      DelayOff();
      QueryMessage1(p);

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
    } else {
      Error(); // нужно обрабатывать ошибку
    }

    DelayMsg();
  }

  return PH2_OK;
}
