/*------------------------------------------------------------------------------
PHONES2_SERIAL!C


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



uint    PushMessage(char*  msT)
{
uint  i = 0;

  while (1)
  {
    if (!*msT) break;
    PushChar(*msT++);
    i++;
  }

  return i;
}


void    QueryMessageMode(void) {
  InitPush(0);
  PushString("AT+CMGF=1\r\n");
  Query(SERIAL_MODEM, 11, 1);
}



void    QueryMessage0(void) {
  InitPush(0);
  PushChar(0x1B);
  Query(0, 1, 1);
  DelayOff();
}



void    QueryMessage1(uchar  ibPhn) {
  InitPush(0);
  PushString("AT+CMGS=");

  line phT = mpphPhones2[ibPhn];

  Clear();
  strcpy(szLo, phT.szLine);

  uchar i;
  for (i=0; i<bLINE_SIZE; i++)
  {
    if (phT.szLine[i] == 0) break;
    PushChar(phT.szLine[i]);
  }

  PushChar(0x0D);

  Query(4, 7+i+2, 1);
}



void    QueryMessage2(bool  fDebug) {
uint  i;

  InitPush(0);

  sprintf(mpbInBuffSave2, "SEM-2 %02u:%02u:%02u %02u.%02u.20%02u - ",
    tiCurr.bHour,
    tiCurr.bMinute,
    tiCurr.bSecond,
    tiCurr.bDay,
    tiCurr.bMonth,
    tiCurr.bYear
  );

  i = PushMessage(mpbInBuffSave2);

  if (fDebug == true)
    sprintf(mpbInBuffSave2+i, "test");
  else
    sprintf(mpbInBuffSave2+i, "prognoz %.3f bolsche limita %.3f !", reCurrPhones2, reMaxxPhones2);

  i += PushMessage(mpbInBuffSave2+i);

  PushChar(0x1A);   // 0x1A - send message, 0x1B - don't send message

  Query(100, i+1, 1);
}
