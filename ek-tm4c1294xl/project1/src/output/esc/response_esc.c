/*------------------------------------------------------------------------------
RESPONSE_ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_esc.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../hardware/memory.h"
#include "../../digitals/wait_query.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../access.h"
#include "esc.h"



void    Esc(uint  wSize)
{
  InitPush(0);
  uchar bT = 0;

  uint i;
  for (i=0; i<wSize; i++)
  {
    bT += SkipChar();
  }

  PushChar(bT);
  Answer(wSize+1, SER_OUTPUT_SLAVE);
}


void    EscError(uchar  bCode)
{
  InitPush(0);

  PushChar(0x1B);
  PushChar(bQuery);
  PushChar(bCode);

  Esc(3);
}



static void ShowCtrlZ()
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Ctrl Z",ibPort+1);
    Clear();
    HideCurrentTime(0);
  }
}


static void ShowEsc(void)
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Esc %c",ibPort+1,bQuery);
    HideCurrentTime(0);
  }
}


void    Esc0(void)
{
  ibActiveEsc = 0xFF;
  mpibActiveEsc[ibPort] = ibActiveEsc;
}


void    EscNumber(void)
{
  uchar i;
  for (i=0; i<bMachineEsc; i++)
  {
    if ((bQuery - 0x31) == (bLogical + i - 1))
      break;
  }

  if (i != bMachineEsc)
  {
    ibActiveEsc = (bQuery - 0x31) - (bLogical - 1);
    mpibActiveEsc[ibPort] = ibActiveEsc;

    InitPush(0);
    PushChar(bQuery);
    Esc(1);

    ShowEsc();
  }
  else
  {
    ibActiveEsc = 0xFF;
    mpibActiveEsc[ibPort] = ibActiveEsc;
  }
}


void    EscA(void)
{
  Beep();
  ShowEsc();
}


void    EscTime(void)
{
  InitPush(0);
  PushChar(ToBCD(tiCurr.bSecond));
  PushChar(ToBCD(tiCurr.bMinute));
  PushChar(ToBCD(tiCurr.bHour  ));
  PushChar(ToBCD(tiCurr.bDay   ));
  PushChar(ToBCD(tiCurr.bMonth ));
  PushChar(ToBCD(tiCurr.bYear  ));
  Esc(6);
}


void    EscVersion(void)
{
  InitPush(0);
  Push("CќЊ+2 V.06 10.10.08!",20);
  PushChar(0x31+ibActiveEsc);
  Esc(21);
}


void    EscDisplay(void)
{
  InitPush(0);

  PushChar(0x0D); PushChar(0x0A); Push(&szHi,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A); Push(&szLo,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A);

  Esc(2*bDISPLAY+3*2);
}


void    EscKey(void)
{
  uchar i = bQuery-'а';
  if (TrueKey(i) == true)
  {
    bKey = mpbKeys[i];
    fKey = true;

    EscDisplay();
  }
  else EscError(bESC_BADDATA);
}


void    EscTransit(void)
{
  if (cbWaitQuery != 0)
  {
    InitPush(0);
    Push("Transit error: busy !",21);
    Esc(21);
  }
  else if (ibPort == 0)
  {
    RunFlow0();

    InitPush(0);
    Push("Transit OK: 1 !",15);
    Esc(15);
  }
  else if (ibPort == 1)
  {
    RunFlow1();

    InitPush(0);
    Push("Transit OK: 1 !",15);
    Esc(15);
  }
}


void    EscId(void)
{
  InitPush(0);
  PushInt(GetRomChecksum());
  PushInt(wPrivate);
  PushChar(bLogical);
  Esc(5);
}



void    RunResponseEsc(void)
{
  if (mpSerial[ibPort] == SER_CTRL_Z)
  {
    mpSerial[ibPort] = SER_BEGIN;

    ShowCtrlZ();
  }
  else if (mpSerial[ibPort] == SER_CHAR)
  {
    mpSerial[ibPort] = SER_BEGIN;

    if (enGlobal == GLB_PROGRAM)
      return;

    if (boBlockEsc == (boolean)0x55)
      return;

    bQuery = InBuff(0);

    ibActiveEsc = mpibActiveEsc[ibPort];

    switch (bQuery)
    {
      case 0x30: Esc0(); return;

      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3A:
      case 0x3B:
      case 0x3C:
      case 0x3D:
      case 0x3E:
      case 0x3F:
      case 0x40: EscNumber(); return;
    }

    if (bQuery == 'A')
    {
      EscA();
      return;
    }

    if (ibActiveEsc >= bMachineEsc) return;

    ShowEsc();

    if (boBlockEsc == TRUE)
    {
      if (bQuery != 'R') 
      {
        InitPush(0);
        Push("Disabled !",10);
        Esc(10);
        return;
      } 
    }

    switch (bQuery)
    {
      case 'T': EscTime(); break;

      case 'R': EscVersion(); break;

      case 'а':
      case 'б':
      case 'в':
      case 'г':
      case 'д':
      case 'е':
      case 'ж':
      case 'з':
      case 'и':
      case 'й':
      case 'к':
      case 'л':
      case 'м':
      case 'н': EscKey(); break;

      case 'о': EscDisplay(); break;

      case 0x1F: EscTransit(); break;

      case 'Ю': EscId(); break;
    }
  }
}



void    RunResponseEsc_All(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseEsc();

  ibPort = 1;
  if (IsFlow1() == 0) RunResponseEsc();

  ibPort = 2;
  RunResponseEsc();

  ibPort = 3;
  RunResponseEsc();
}
