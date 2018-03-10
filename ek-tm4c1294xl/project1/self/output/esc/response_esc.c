/*------------------------------------------------------------------------------
RESPONSE_ESC!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_esc.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../hardware/memory.h"
#include "../../digitals/wait_query.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../tariffs/tariffs.h"
#include "../../tariffs/zones.h"
#include "../../tariffs/relaxs.h"
#include "../../time/rtc.h"
#include "../../flash/flash.h"
#include "../../access.h"
#include "../../groups.h"
#include "esc.h"



static void PushFloatBCD(float  fl)
{
  ulong dw = (ulong)fl;

  PushChar( ToBCD(dw % 100)           );
  PushChar( ToBCD((dw % 10000) / 100) );
  PushChar( ToBCD(dw / 10000)         );
}


static void PushZone(void)
{
  uchar i;
  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);

    PushChar( ToBCD(brAlt.bMinute) );
    PushChar( ToBCD(brAlt.bHour) | ((brAlt.ibTariff << 6) & 0xC0) );
  }

  for (i=GetZoneAltSize(); i<6; i++)
  {
    PushChar(0xAA);
    PushChar(0xAA);
  }
}



static void Esc(uint  wSize)
{
  InitPush(0);
  uchar b = 0;

  uint i;
  for (i=0; i<wSize; i++)
  {
    b += SkipChar();
  }

  PushChar(b);
  Answer(wSize+1, SER_OUTPUT_SLAVE);
}


static void EscError(uchar  bCode)
{
  InitPush(0);

  PushChar(0x1B);
  PushChar(bQuery);
  PushChar(bCode);

  Esc(3);
}



static void ShowCtrlZ()
{
  if (wProgram == bTEST_REQUEST)
  {
    ibPortActive = ibPort;
    HideCurrTime(0);
  }

  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Ctrl Z",ibPort+1);

    ibPortActive = ibPort;
    HideCurrTime(0);
  }
}


static void ShowEsc(void)
{
  if (wProgram == bTEST_REQUEST)
  {
    ibPortActive = ibPort;
    HideCurrTime(0);
  }

  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Esc %c",ibPort+1,bQuery);

    ibPortActive = ibPort;
    HideCurrTime(0);
  }
}


static void Esc0(void)
{
  ibActiveEsc = 0xFF;
  mpibActiveEsc[ibPort] = ibActiveEsc;
}


static void EscNumber(void)
{
  uchar i;
  for (i=0; i<bMachinesEsc; i++)
  {
    if ((bQuery - 0x31) == (bLogical + i - 1))
      break;
  }

  if (i != bMachinesEsc)
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


static void Esc_A(void)
{
  Beep();
  ShowEsc();
}


static void Esc_T(void)
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


static void Esc_R(void)
{
  InitPush(0);
  Push("CќЊ+2 V.06 10.10.08!",20);
  PushChar(0x31+ibActiveEsc);
  Esc(21);
}


static void Esc_w(void)
{
uchar   i, j;

  InitPush(0);

  // первый байт состояния
  i = bOldTrfMode;

  if (GetMode(*GetCurrTimeDate()) != 0)
    i |= 0x04;

  if (enGlobal == GLB_REPROGRAM)
    i |= 0x20;

  PushChar(i);

  // второй байт состояния
  if (bOldTrfMode == 4)
    PushChar(4);
  else
    PushChar(0);

  // дата/время первого запуска
  PushChar( ToBCD(tiStart.bSecond) );
  PushChar( ToBCD(tiStart.bMinute) );
  PushChar( ToBCD(tiStart.bHour  ) );
  PushChar( ToBCD(tiStart.bDay   ) );
  PushChar( ToBCD(tiStart.bMonth ) );
  PushChar( ToBCD(tiStart.bYear  ) );

  // тарифные зоны по кварталам
  memset(&zoAlt, 0, sizeof(zoAlt));
  PushZone();
  PushZone();
  PushZone();
  PushZone();

  // тарифные зоны текущего месяца
  zoAlt = *PGetZonePowMonthMode(tiCurr.bMonth - 1, 0);
  PushZone();

  // список праздников
  for (i=0; i<GetRelaxSize(); i++)
  {
    if (i >= 20) break;

    GetRelaxDate(i);
    PushChar( ToBCD(tiRelax.bDay)   );
    PushChar( ToBCD(tiRelax.bMonth) );
  }

  while (i++ < 20)
  {
    PushChar(0x55);
    PushChar(0x55);
  }

  // соcтав групп: все каналы
  for (i=bFRAMES*ibActiveEsc; i<bFRAMES*(1+ibActiveEsc); i++)
  {
    uint w = 0;

    for (j=0; j<GetGroupsSize(i); j++)
    {
      if (j > 16) break;
      w |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
    }

    PushChar(w % 0x100);
    PushChar(w / 0x100);
  }

  // соcтав групп: каналы с отрицательным знаком
  for (i=bFRAMES*ibActiveEsc; i<bFRAMES*(1+ibActiveEsc); i++)
  {
    uint w = 0;

    for (j=0; j<GetGroupsSize(i); j++)
    {
      if (j > 16) break;
      if (GetGroupsNodeSign(i,j) == 1)
        w |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
    }

    PushChar(w % 0x100);
    PushChar(w / 0x100);
  }

  // коэффициенты трансформации
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mpdbTransEng[i+16*ibActiveEsc]);
  }

  // коэффициенты преобразования
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mpdbPulseHou[i+16*ibActiveEsc]);
  }

  // лимиты
  for (i=0; i<18; i++)
    PushChar(0);

  // заводской номер
  PushChar( ToBCD(wPrivate % 100)         );
  PushChar( ToBCD((wPrivate % 10000)/100) );
  PushChar( ToBCD(wPrivate / 10000)       );

  // заводской номер
  PushChar( ToBCD(wPrivate % 100)         );
  PushChar( ToBCD((wPrivate % 10000)/100) );
  PushChar( ToBCD(wPrivate / 10000)       );

  // коэффициенты потерь
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mpdbLosse[i+16*ibActiveEsc] * 1000000);
  }

  Esc(300);
}


static void Esc_W(void)
{
uchar   i;

  InitPush(0);

  if (GetFlashStatus() == 0)
    i = 0x07;                            // норма
  else
    i = 0x01;                            // ошибка флэш-памяти

  if (cbSwitchOn == 0)
    PushChar(i | 0x08);
  else
  if (cbSwitchOn == 1)
    PushChar(i | 0x10);
  else
    PushChar(i);

  PushTime(tiPowerOff);                  // время последнего выключения питания
  PushTime(tiPowerOn);                   // время последнего включения питания
  PushChar(cbSwitchOn);                   // количество выключений питания

  PushChar(0);                           // время выключения за предыдущий месяц (дней, часов, минут)
  PushChar(0);
  PushChar(0);

  PushChar(0);                           // время выключения за текущий месяц (дней, часов, минут)
  PushChar(0);
  PushChar(0);

  Esc(20);
}


static void EscTariffs(void)
{
  InitPush(0);

  uchar m;
  for (m=0; m<12; m++)
  {
    zoAlt = *PGetZonePowMonthMode(m, 0);
    PushZone();
  }

  for (m=0; m<12; m++)
  {
    zoAlt = *PGetZoneEngMonthMode(m, 0);
    PushZone();
  }

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  if (fPublicTrf == false)
    PushChar(1);
  else
    PushChar(0);

  if (fPublicTrfPrevMon == false)
    PushChar(1);
  else
    PushChar(0);

  Esc(300);
}


static void EscDisplay(void)
{
  InitPush(0);

  PushChar(0x0D); PushChar(0x0A); Push(&szHi,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A); Push(&szLo,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A);

  Esc(2*bDISPLAY+3*2);
}


static void EscKey(void)
{
  uchar i = bQuery-'а';
  if (ValidKey(i) == true)
  {
    bKey = mpbKeys[i];
    fKey = true;

    EscDisplay();
  }
  else EscError(bESC_BADDATA);
}


static void EscTransit(void)
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


static void EscId(void)
{
  InitPush(0);
  PushIntBig(GetRomChecksum());
  PushIntBig(wPrivate);
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

    if (boBlockEsc == (bool)0x55)
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

      case 'A': Esc_A(); return;
    }

    if (ibActiveEsc >= bMachinesEsc) return;

    ShowEsc();

    if (boBlockEsc == true)
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
      case 'T': Esc_T(); break;
      case 'R': Esc_R(); break;
      case 'w': Esc_w(); break;
      case 'W': Esc_W(); break;

      case '*': EscTariffs(); break;

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

#ifdef NO_DISPLAY
void    RunResponseEsc_Panel(void)
{
  if (mpSerial[ibPort] == SER_CTRL_Z)
  {
    mpSerial[ibPort] = SER_BEGIN;

    ShowCtrlZ();
  }
  else if (mpSerial[ibPort] == SER_CHAR)
  {
    mpSerial[ibPort] = SER_BEGIN;

    bQuery = InBuff(0);

    ibActiveEsc = mpibActiveEsc[ibPort];

    switch (bQuery)
    {
      case 'A': Esc_A(); return;
    }

    ShowEsc();

    switch (bQuery)
    {
      case 'T': Esc_T(); break;
      case 'R': Esc_R(); break;

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

      case 'Ю': EscId(); break;
    }
  }
}
#endif


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

#ifdef NO_DISPLAY
void    RunResponseEsc_All_Panel(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseEsc_Panel();

  ibPort = 2;
  RunResponseEsc_Panel();
}
#endif
