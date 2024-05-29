/*------------------------------------------------------------------------------
OUT_TRANSIT!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../keyboard/keyboard.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../serial/save_in_buff.h"
#include "../serial/speeds.h"
#include "../serial/monitor.h"
#include "../sensors/unpack_k.h"
#include "../sensors/unpack_w.h"
#include "../sensors/sensor40/decompress40.h"
#include "../digitals/wait_answer.h"
#include "../hardware/watchdog.h"
#include "out_transit.h"



void    SafeTransitExecute1(void )
{
uint    i;
uchar   j;

  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    j = ibPort;

    ibPort = bInBuff5;

    InitPush(0);
    for (i=0; i<iwInBuffSave-10; i++) PushChar(mpbInBuffSave[i+8]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-10, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    if (mpSerial[ibPort] != SER_POSTINPUT_MASTER)
    {
      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      Result(bRES_BADMODE);
    }
    else
    {
      SaveInBuff();
      iwInBuffSave = IndexInBuff();

      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      InitPushCRC();
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
      Output(iwInBuffSave);
    }
  }
}


void    SafeTransitExecute2(void)
{
uint    i;
uchar   j;

  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    j = ibPort;

    ibPort = bInBuff5;

    InitPush(0);
    for (i=0; i<iwInBuffSave-10; i++) PushChar(mpbInBuffSave[i+8]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-10, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    if (mpSerial[ibPort] != SER_POSTINPUT_MASTER)
    {
      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      Result(bRES_BADMODE);
    }
    else
    {
      SaveInBuff();
      iwInBuffSave = IndexInBuff();

      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      InitPushCRC();
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
      Output(iwInBuffSave);
    }
  }
}



void    SafeTransitExecute3(void)
{
uint    i;
uchar   j;

  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    j = ibPort;

    ibPort = bInBuff5;

    cbHeaderBcc = bInBuff8;
    cwInBuffBcc = 0;

    InitPush(0);
    for (i=0; i<iwInBuffSave-11; i++) PushChar(mpbInBuffSave[i+9]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-11, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_INPUT_MASTER)
        DecompressK(0);

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    MonitorIn();

    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    mpSerial[ibPort] = SER_BEGIN;
    ibPort = j;

    InitPushCRC();
    if (iwInBuffSave > 0)
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output(iwInBuffSave);
  }
}



void    SafeTransitExecute4(void)
{
uint    i;
uchar   j;

  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    j = ibPort;

    ibPort = bInBuff5;

    InitPush(0);
    for (i=0; i<iwInBuffSave-10; i++) PushChar(mpbInBuffSave[i+8]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-10, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    mpSerial[ibPort] = SER_BEGIN;
    ibPort = j;

    InitPushCRC();
    for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output(iwInBuffSave);
  }
}



void    TransitW(void)
{
  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff5;

    cbHeaderBcc = bInBuff8;
    cwInBuffBcc = 0;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-11; i++) PushChar(mpbInBuffSave[i+9]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-11, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_INPUT_MASTER)
        UnpackW(false,3);

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    MonitorIn();

    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    mpSerial[ibPort] = SER_BEGIN;
    ibPort = p;

    InitPushCRC();
    if (iwInBuffSave > 0)
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output(iwInBuffSave);
  }
}



void    SafeTransitDevice40(void)
{
uint    i;
uchar   j;

  if (bInBuff5 >= bPORTS)
    Result(bRES_BADADDRESS);
  else if (IsSlave(bInBuff5))
    Result(bRES_BADPORT);
  else if (IndexInBuff() <= 10)
    Result(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    j = ibPort;

    ibPort = bInBuff5;

    InitPush(0);
    for (i=0; i<iwInBuffSave-10; i++) PushChar(mpbInBuffSave[i+8]);
    Query(bInBuff6+bInBuff7*0x100, iwInBuffSave-10, 1);

    InitWaitAnswer();

    while (1)
    {
      if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

      ResetWatchdog();
      ShowWaitAnswer(1);
      if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

      if (mpSerial[ibPort] == SER_INPUT_MASTER)
        Decompress40();

      if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
        break;
      else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
               (mpSerial[ibPort] == SER_BADLINK)) break;
    }

    if (mpSerial[ibPort] != SER_POSTINPUT_MASTER)
    {
      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      Result(bRES_BADMODE);
    }
    else
    {
      SaveInBuff();
      iwInBuffSave = IndexInBuff();

      mpSerial[ibPort] = SER_BEGIN;
      ibPort = j;

      InitPush(0);
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
      Answer(iwInBuffSave, SER_OUTPUT_SLAVE);
    }
  }
}
