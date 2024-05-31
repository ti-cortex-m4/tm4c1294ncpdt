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
//#include "../serial/monitor.h"
//#include "../sensors/unpack_k.h"
//#include "../sensors/unpack_w.h"
//#include "../sensors/sensor40/decompress40.h"
#include "../../digitals/wait_answer.h"
#include "../../hardware/watchdog.h"
#include "u_transit2.h"



#ifndef MODBUS

void    GetTransitExecuteUni1(void)
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

//void    GetTransitExecuteUni1(void)
//{
//uint    i;
//
//  for (i=0; i<IndexInBuff()-10; i++) SetInBuff(i, InBuff(i+6));
//  SetIndexInBuff(IndexInBuff()-10);
//
//  mpSerial[ibPort] = SER_POSTINPUT_SLAVE;
//}

#endif
