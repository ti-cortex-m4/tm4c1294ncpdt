/*------------------------------------------------------------------------------
SLAVE_MODEM.C


-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../display/display.h"
#include "../time/delay.h"



static void EscAT(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);

  DelayMsg();

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


static void SlaveModem(void)
{
  if ((boSlaveModem == true) && (mpanSendAT[ibPort] == ANS_ANSWER))
  {
    mpanSendAT[ibPort] = ANS_BEGIN;

    SaveDisplay();

    ShowHi(szClear); sprintf(szHi,"Порт %u: AT",ibPort+1);

    Clear();
    DelayMsg();

    LoadDisplay();

    EscAT();
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

