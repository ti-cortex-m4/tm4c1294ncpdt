/*------------------------------------------------------------------------------
u_transit2.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/save_in_buff.h"
#include "../../serial/speeds.h"
#include "../../serial/monitor.h"
#include "../../sensors/unpack_k.h"
#include "../../sensors/unpack_w.h"
#include "../../sensors/sensor40/decompress40.h"
#include "../../digitals/wait_answer.h"
#include "../../hardware/watchdog.h"
#include "response_uni.h"
#include "u_transit2.h"



#ifndef MODBUS

void    GetTransitExecuteUni1(void)
{
  if (bInBuff6 >= bPORTS)
    Result2(bRES_BADADDRESS);
  else if (IsSlave(bInBuff6))
    Result2(bRES_BADPORT);
  else if (IndexInBuff() <= 13)
    Result2(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff6;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-13; i++) PushChar(mpbInBuffSave[i+9]);
    Query(bInBuff8+bInBuff7*0x100, iwInBuffSave-13, 1);

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
      ibPort = p;

      Result2(bRES_BADMODE);
    }
    else
    {
      SaveInBuff();
      iwInBuffSave = IndexInBuff();

      mpSerial[ibPort] = SER_BEGIN;
      ibPort = p;

      InitPushUni();
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
      Output2(iwInBuffSave);
    }
  }
}


void    GetTransitExecuteUni3(void)
{
  if (bInBuff6 >= bPORTS)
    Result2(bRES_BADADDRESS);
  else if (IsSlave(bInBuff6))
    Result2(bRES_BADPORT);
  else if (IndexInBuff() <= 13)
    Result2(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff6;

    cbHeaderBcc = bInBuff8;
    cwInBuffBcc = 0;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-14; i++) PushChar(mpbInBuffSave[i+10]);
    Query(bInBuff8+bInBuff7*0x100, iwInBuffSave-14, 1);

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
    ibPort = p;

    InitPushUni();
    if (iwInBuffSave > 0)
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output2(iwInBuffSave);
  }
}


void    GetTransitExecuteUni4(void)
{
  if (bInBuff6 >= bPORTS)
    Result2(bRES_BADADDRESS);
  else if (IsSlave(bInBuff6))
    Result2(bRES_BADPORT);
  else if (IndexInBuff() <= 13)
    Result2(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff6;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-13; i++) PushChar(mpbInBuffSave[i+9]);
    Query(bInBuff8+bInBuff7*0x100, iwInBuffSave-13, 1);

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
    ibPort = p;

    InitPushUni();
    for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output2(iwInBuffSave);
  }
}


void    GetTransitExecuteUniW(void)
{
  if (bInBuff6 >= bPORTS)
    Result2(bRES_BADADDRESS);
  else if (IsSlave(bInBuff6))
    Result2(bRES_BADPORT);
  else if (IndexInBuff() <= 13)
    Result2(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff6;

    cbHeaderBcc = bInBuff8;
    cwInBuffBcc = 0;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-14; i++) PushChar(mpbInBuffSave[i+10]);
    Query(bInBuff8+bInBuff7*0x100, iwInBuffSave-14, 1);

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

    InitPushUni();
    if (iwInBuffSave > 0)
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
    Output2(iwInBuffSave);
  }
}


void    GetTransitExecuteUni40(void)
{
  if (bInBuff6 >= bPORTS)
    Result2(bRES_BADADDRESS);
  else if (IsSlave(bInBuff6))
    Result2(bRES_BADPORT);
  else if (IndexInBuff() <= 13)
    Result2(bRES_BADDATA);
  else
  {
    SaveInBuff();
    iwInBuffSave = IndexInBuff();

    uchar p = ibPort;
    ibPort = bInBuff6;

    InitPush(0);
    uint i;
    for (i=0; i<iwInBuffSave-13; i++) PushChar(mpbInBuffSave[i+9]);
    Query(bInBuff8+bInBuff7*0x100, iwInBuffSave-13, 1);

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
      ibPort = p;

      Result2(bRES_BADMODE);
    }
    else
    {
      SaveInBuff();
      iwInBuffSave = IndexInBuff();

      mpSerial[ibPort] = SER_BEGIN;
      ibPort = p;

      InitPush(0);
      for (i=0; i<iwInBuffSave; i++) PushChar(mpbInBuffSave[i]);
      Answer(iwInBuffSave, SER_OUTPUT_SLAVE);
    }
  }
}

#endif