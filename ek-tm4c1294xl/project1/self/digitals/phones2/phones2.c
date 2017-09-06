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
#include "phones2_modem.h"
#include "phones2.h"



// прогнозируемая мощность
float                   reValPhones2;

// буфера
uchar                   mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];

// таймаут
uchar                   bDelayPhone2;

// буфер
stamp2                  mpstPhones2[PHONE2_CODES];

// буфер
uchar                   mpbBuffPhones2[PHONE2_RECORD];

// счётчики
ulong                   cdwPhones20, cdwPhones21, cdwPhones22, cdwPhones23, cdwPhones24, cdwPhones25;

// промежуточный буфер
char                    mpbInBuffSave2[100];



cache const           	chPortPhones2 = {PORT_PHONES2, &bPortPhones2, sizeof(uchar)};
cache const             chPhones2 = {PHONES2, &mpphPhones2, sizeof(mpphPhones2)};
cache const             chMaxPhones2 = {MAX_PHONES2, &reMaxPhones2, sizeof(float)};



void    InitPhones2(void) {
  LoadCacheChar(&chPortPhones2, 0, bPORTS, 0);
  LoadCache(&chPhones2);
  LoadCache(&chMaxPhones2);
}


void    ResetPhones2(void) {

  SaveCacheChar(&chPortPhones2, 0);


  reValPhones2 = 0;

  reMaxPhones2 = 1000;
  SaveCache(&chMaxPhones2);


  memset(&mpphPhones2, 0, sizeof(mpphPhones2));

  uchar p;
  for (p=0; p<bPHONES2; p++)
  {
    mpphPhones2[p].szLine[0] = '0';
  }
  SaveCache(&chPhones2);


  bDelayPhone2 = 0;


  memset(&mpbAnswer1Phones2, 0, sizeof(mpbAnswer1Phones2));
  memset(&mpbAnswer2Phones2, 0, sizeof(mpbAnswer2Phones2));


  uchar i;
  for (i=0; i<PHONE2_CODES; i++) {
    mpstPhones2[i].cwSelf = 0;
    mpstPhones2[i].tiSelf = tiZero;
  }


  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));


  cdwPhones20 = 0;
  cdwPhones21 = 0;
  cdwPhones22 = 0;
  cdwPhones23 = 0;
  cdwPhones24 = 0;
  cdwPhones25 = 0;
}



bool    UsePhones2(void) {
  return ((bPortPhones2 > 0) && (bPortPhones2 <= bPORTS));
}
