/*------------------------------------------------------------------------------
PORTS_MODEMS.H


------------------------------------------------------------------------------*/

#include        "../main.h"
//#include        "../memory/mem_ports.h"
#include        "../keyboard/keyboard.h"
#include        "../hardware/watchdog.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
//#include        "../isr/serial0.h"
//#include        "../isr/serial1.h"
//#include        "../isr/serial2.h"
//#include        "../isr/serial3.h"
//#include        "../crc-16.h"
#include        "ports.h"



bool    MakePhones2Input0(void) {
uchar i;

  memset(&mpbAnswer1Phones2, 0, sizeof(mpbAnswer1Phones2));
  InitPop(0);
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
uchar i;

  memset(&mpbAnswer2Phones2, 0, sizeof(mpbAnswer2Phones2));
  InitPop(0);
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

    ResetWDT();
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

    ResetWDT();
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



serial  ModInput(uchar  bSecond, bool  fShow)
{
  MakeLongPause(DEV_MODEM_MANUAL, bSecond);
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWDT();
    ShowWaitAnswer(fShow);

    if (GetCurr() == DEV_MODEM_MANUAL) break;

    if ((mpSerial[ibPort] == SER_OVERFLOW) ||
        (mpSerial[ibPort] == SER_BADLINK)  ||
        (mpSerial[ibPort] == SER_POSTANSWER_MODEM) ||
        (mpSerial[ibPort] == SER_PAUSE)) break;

  }

  SetCurr(DEV_MODEM_MANUAL);
  NoShowTime(0);

  return( mpSerial[ibPort] );
}


bool    ModInputOK(uchar  bSecond)
{
  return( (ModInput(bSecond,0) == SER_POSTANSWER_MODEM) && (GetModemAnswer() == 0) );
}


bool    ModSerialOK(void)
{
  return( (mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (GetModemAnswer() == 0) );
}
