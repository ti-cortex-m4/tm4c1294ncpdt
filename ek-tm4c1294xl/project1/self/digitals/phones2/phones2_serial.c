/*------------------------------------------------------------------------------
PHONES2_SERIAL*C


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

  line ph = mpphPhones2[ibPhn];

  Clear();
  strcpy(szLo, ph.szLine);

  uchar i;
  for (i=0; i<bLINE_SIZE; i++)
  {
    if (ph.szLine[i] == 0) break;
    PushChar(ph.szLine[i]);
  }

  PushChar(0x0D);

  Query(4, 7+i+2, 1);
}



void    QueryMessage2(bool  fDebug) {
  uint wSize = 0;

  InitPush(0);

  wSize += PushString("SEM-2 ");

  wSize += PushCharDec2Txt(tiCurr.bHour);
  wSize += PushString(":");
  wSize += PushCharDec2Txt(tiCurr.bMinute);
  wSize += PushString(":");
  wSize += PushCharDec2Txt(tiCurr.bSecond);
  wSize += PushString(" ");
  wSize += PushCharDec2Txt(tiCurr.bDay);
  wSize += PushString(".");
  wSize += PushCharDec2Txt(tiCurr.bMonth);
  wSize += PushString(".20");
  wSize += PushCharDec2Txt(tiCurr.bYear);
  wSize += PushString(" - ");

  if (fDebug == true) {
    wSize += PushString("test");
  }
  else {
    wSize += PushString("prognoz ");
    wSize += PushFloat3(reValPhones2);
    wSize += PushString(" bolsche limita ");
    wSize += PushFloat3(reMaxPhones2);
    wSize += PushString(" !");
  }

  wSize += PushChar(0x1A);   // 0x1A - send message, 0x1B - don't send message

  Query(100, wSize+1, 1);
}
