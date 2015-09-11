/*------------------------------------------------------------------------------
SLAVE_MODEM.C


-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "slave_modem.h"



cache const             chSlaveModem = {SLAVE_MODEM, &fSlaveModem, sizeof(bool)};



void    InitSlaveModem(void)
{
  LoadCacheBool(&chSlaveModem, false);
}


void    ResetSlaveModem(void)
{
	fSlaveModem = false;
  SaveCache(&chSlaveModem);
}



static void SendAT1(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);
}


static void SendAT2(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('&'); // &D0 - игнорировать сигнал DTR
  PushChar('D');
  PushChar('0');

  PushChar('&'); // &K0 - управление потоком запрещено
  PushChar('K');
  PushChar('0');

  PushChar('S'); // S0=2 - подъём телефонной трубки на втором гудке
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Answer(8,SER_OUTPUT_SLAVE);
}


static void SendAT(void)
{
  SendAT1();

  DelayMsg();

  SendAT2();
}



static void SlaveModem(void)
{
  if ((fSlaveModem == true) && (mpstSendAT[ibPort] == AT_ANSWER))
  {
    mpstSendAT[ibPort] = AT_BEGIN;

    SaveDisplay();

    ShowHi(szClear); sprintf(szHi,"Порт %u: AT",ibPort+1);

    Clear();
    DelayMsg();

    LoadDisplay();

    SendAT();
    fSendAT = 0;
  }
}


void    SlaveModem_All(void)
{
  ibPort = 0;
  SlaveModem();

  ibPort = 1;
  SlaveModem();

  ibPort = 2;
  SlaveModem();

  ibPort = 3;
  SlaveModem();
}



void    InitSerial_SlaveModem(uchar  ibPrt)
{
  ASSERT(ibPrt < bPOSTS);

  mpcbSendAT[ibPrt] = bSEND_AT_TIMEOUT;
  mpstSendAT[ibPrt] = AT_TIMEOUT;
}


void    SlaveModem_1Hz(void)
{
  uchar p;
  for (p=0; p<PORTS; p++)
  {
    if (mpstSendAT[p] == AT_TIMEOUT)
    {
      (mpcbSendAT[p] == 0) ? (mpstSendAT[p] = AT_ANSWER) : (mpcbSendAT[p]--);
    }
  }
}
