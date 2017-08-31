/*------------------------------------------------------------------------------
PHONES22!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_settings.h"
//#include "../../memory/mem_digitals.h"
//#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports_push.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "../../digitals/wait_answer.h"
#include "../../hardware/watchdog.h"
#include "phones2.h"
#include "phones22.h"



extern uchar                  mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];



bool    MakePhones2Input0(void) {
  memset(&mpbAnswer1Phones2, 0, sizeof(mpbAnswer1Phones2));
  InitPop(0);

  uchar i;
  for (i=0; i<IndexInBuff(); i++) {
    if (i >= PHONE2_ANSWER) break;
    mpbAnswer1Phones2[i] = PopChar();
  }

  if (IndexInBuff() != 4) return 0;

  InitPop(0);
  if (PopChar() != 0x0D) return 0;
  if (PopChar() != 0x0A) return 0;
  if (PopChar() != 0x3E) return 0;
  if (PopChar() != 0x20) return 0;

  return 1;
}


bool    MakePhones2Input1(void) {
  memset(&mpbAnswer2Phones2, 0, sizeof(mpbAnswer2Phones2));
  InitPop(0);

  uchar i;
  for (i=0; i<IndexInBuff(); i++) {
    if (i >= PHONE2_ANSWER) break;
    mpbAnswer2Phones2[i] = PopChar();
  }

  if (IndexInBuff() < 2) return 0;

  InitPop(IndexInBuff() - 2);
  if (PopChar() != 0x30) return 0;
  if (PopChar() != 0x0D) return 0;

  return 1;
}


bool    Phones2Answer(void)  {
  return  (IndexInBuff() >= 2);
}


uchar   Phones2Result(void)  {
  InitPop(IndexInBuff() - 2);
  return  PopChar();
}


serial  Phones2Input0(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (MakePhones2Input0())
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}


serial  Phones2Input1(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { if (MakePhones2Input1()) mpSerial[ibPort] = SER_GOODCHECK; else mpSerial[ibPort] = SER_BADCHECK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      mpSerial[ibPort] = SER_BADCHECK;
      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}

