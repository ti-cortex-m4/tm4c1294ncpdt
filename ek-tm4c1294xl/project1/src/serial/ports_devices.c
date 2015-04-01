/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../keyboard/keyboard.h"
#include        "../hardware/watchdog.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
#include        "../isr/serial0.h"
#include        "../isr/serial1.h"
#include        "../isr/serial2.h"
#include        "../isr/serial3.h"
#include        "../kernel/crc-16.h"
#include        "../display/display.h"
#include        "../time/delay.h"
#include        "ports.h"
#include        "ports_devices.h"



void    Query(uint  cwIn, uchar  cbOut, bool  fMinor)
{
//  DebugOut(cwIn, cbOut);

  // при передаче порт переключается в ведущий режим из временного ведомого
  mpboLocal[ibPort] = FALSE;

  // включаем защитный интервал обращения к счётчикам (кроме переключения в временный ведомый режим из ведущего)
  if (cwIn != SERIAL_LOCAL) cbWaitQuery = bMAXWAITQUERY;

  switch (ibPort)
  {
    case 0:  Query0(cwIn, cbOut, fMinor);  break;
    case 1:  Query1(cwIn, cbOut, fMinor);  break;
    case 2:  Query2(cwIn, cbOut, fMinor);  break;
    case 3:  Query3(cwIn, cbOut, fMinor);  break;
  }
}



// передача запроса по прерыванию (из выходного буфера)
void    QueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush(0);
  Skip(cbOut-2);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Query(cwIn,cbOut,1);
}



serial  Input(void)
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
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
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



#ifndef SKIP_C

// передача запроса по прерыванию (из выходного буфера)
void    RevQueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush();
  bOutputC0 = SkipChar();
  bOutputC1 = SkipChar();
  bOutputC2 = SkipChar();

  InitPush();
  Skip(cbOut-2);

  PushChar(bCRCLo);
  PushChar(bCRCHi);

  Query(cwIn,cbOut,1);
}


bool    RevLinkErrors(void)
{
  if (InBuff(0) != bOutputC0) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if ((InBuff(1) & 0x7F) != bOutputC1) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if (InBuff(2) != bOutputC2) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  return 0;
}


serial  RevInput(void)
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
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

          if (RevLinkErrors() == 0)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
          ChecksumError();
        }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}

#endif



void    TestResult(uchar  bT)
{
  if (bT != 0)
  {
    Clear();
    sprintf(szLo+1,"код ответа: %02X ",bT);
    DelayInf();
  }
}
