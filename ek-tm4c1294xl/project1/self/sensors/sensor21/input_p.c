/*------------------------------------------------------------------------------
INPUT_P.H


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_ports.h"
//#include "../memory/mem_serial3.h"
//#include "../memory/mem_profile.h"
//#include "../keyboard/keyboard.h"
//#include "../hardware/watchdog.h"
//#include "../digitals/wait_answer.h"
//#include "../digitals/wait_query.h"
//#include "../devices/devices.h"
//#include "../sensors/unpack_k.h"
//#include "../isr/serial.h"
//#include "../isr/serial0.h"
//#include "../isr/serial1.h"
//#include "../isr/serial2.h"
//#include "../isr/serial3.h"
//#include "../kernel/crc-16.h"
//#include "../kernel/crc_els.h"
//#include "../display/display.h"
//#include "../time/delay.h"
//#include "../serial/monitor.h"
//#include "../serial/print2.h"
//#include "monitor.h"
//#include "input.h"
//#include "ports.h"
//#include "ports_devices.h"
#include "input_p.h"



void    ElsQueryIO(uint  cbIn, uchar  cbOut)
{
uchar	i,bT;

  InitPush(0);
  SkipChar();

  bT = 0;
  for (i=0; i<cbOut-2; i++) bT ^= SkipChar();
  PushChar(bT);

#ifdef  TRANSIT_ENABLED
  QueryT(cbIn,cbOut,1);
#else
  Query(cbIn,cbOut,1);
#endif
}


bool    MakeElsInBuff0(void)
{
uchar	i,bT;

//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() < 2) return 0;

  InitPop(1);
  bT = 0;
  for (i=0; i<IndexInBuff()-2; i++) bT ^= PopChar();

  return (bT == PopChar());
}


bool    MakeElsInBuff1(void)
{
//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() < 2) return 0;

  InitPop(IndexInBuff()-2);
  if (PopChar() != 0x0D) return 0;
  if (PopChar() != 0x0A) return 0;

  return 1;
}


bool    MakeElsInBuff2(void)
{
//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() != 1) return 0;

  InitPop(0);
  return (PopChar() == 0x06);
}


serial  ElsInput(uchar  bMode)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (bMode == 0)
      {
        if ( MakeElsInBuff0() ) {
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }
      else if (bMode == 1)
      {
        if ( MakeElsInBuff1() ) {
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }
      else
      {
        if ( MakeElsInBuff2() ) {
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}


serial  ElsInputRD(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      MakeCRCElsInBuff(0, CountInBuff());

      if (wCrcEls == 0) {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else {
        mpSerial[ibPort] = SER_BADCHECK;
      }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}
