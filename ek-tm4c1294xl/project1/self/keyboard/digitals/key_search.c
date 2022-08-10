/*------------------------------------------------------------------------------
KEY_SEARCH!C

 Поиск цифровых счётчиков
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../display/display.h"
#include "../../display/panel.h"
#include "../keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/modems.h"
#include "../../serial/ports_modems.h"
#include "../../serial/speeds.h"
#include "../../serial/speeds_display.h"
#include "../../digitals/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_display.h"
#include "../../sensors/device_a.h"
#include "../../sensors/device_b.h"
#include "../../sensors/sensor3/device_c.h"
#include "../../sensors/sensor34/device34.h"
#include "../../sensors/sensor38/automatic38.h"
#include "../../sensors/sensor39/automatic39.h"



//                                         0123456789ABCDEF
static char const       szSearch[]      = "Поиск устройств ",
                        szBySpeed[]     = "  по скоростям  ",
                        szByNumber[]    = "  по номерами   ";



static uchar            ibXmax, ibYmin, ibYmax;



void    ShowFoundNumber(uchar  i)
{
  Beep();
  sprintf(szLo+10,"%03u",i);
}



bool    ChangeSpeedModem(void)
{
  DelayOff();
  QueryModemBaud(0);

  if (ModInputOK(1) == 0) ;

  DelayOff();
  QueryModemCommon(0);

  if (ModInputOK(1) == 0) return(0);

  Beep();
  sprintf(szLo+10,"OK");

  return(1);
}



#ifndef SKIP_A

bool    ChangeSpeedA(void)
{
  InitPush(0);
  PushChar(0);
  PushChar(0);                          // тест канала связи

  QueryIO(2+2, 2+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  diCurr.bAddress = 0;                  // открытие канала связи

  QueryOpenA();
  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  InitPush(0);
  PushChar(0);
  PushChar(8);
  PushChar(5);                          // чтение сетевого адреса

  QueryIO(2+1+2, 2+1+2);

  if (Input() != SER_GOODCHECK) return(0);

  ShowFoundNumber(InBuff(2));
  return(1);
}

#endif



#ifndef SKIP_B

bool    ChangeSpeedB(void)
{
  InitPush(0);
  PushChar(0);
  PushChar(0);                          // тест канала связи

  QueryIO(2+2, 2+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  diCurr.bAddress = 0;                  // открытие канала связи

  QueryOpenB();
  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  InitPush(0);
  PushChar(0);
  PushChar(8);
  PushChar(5);                          // чтение сетевого адреса

  QueryIO(2+1+2, 2+1+2);

  if (Input() != SER_GOODCHECK) return(0);

  ShowFoundNumber(InBuff(2));
  return(1);
}

#endif



#ifndef SKIP_C

bool    ChangeSpeedC(void)
{
  InitPush(0);
  PushChar(0);
  PushChar(3);
  PushChar(21);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(3+2+2, 3+3+2);

  if (RevInput() != SER_GOODCHECK) return(0);
  Beep();

  ShowFoundNumber(InBuff(4));
  return(1);
}

#endif



#ifndef SKIP_E

bool    ChangeSpeedE(void)
{
uchar   i;

  for (i=1; i<=16; i++)
  {
    sprintf(szLo+10," %-3bu",i);

    QueryBreakE();

    InitPush(0);
    PushChar(0x1B);
    PushChar('0'+i);

    Query(1+1, 2, 1);

    if (EscInput() == SER_GOODCHECK)
    {
      ShowFoundNumber(i);
      return(1);
    }

    if (fKey == true) return(0);
  }

  return(0);
}

#endif



#ifndef SKIP_F

bool    ChangeSpeedF(void)
{
  QueryBreakF();

  InitPushPck();
  PushChar(0);                          // логический номер
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETLOGICAL);            // номер функции

  PckQueryIO(2+7, 0+7);

  if (Input() != SER_GOODCHECK) return(0);

  ShowFoundNumber(InBuff(5));
  return(1);
}

#endif



#ifndef SKIP_N

bool    ChangeSpeedN(void)
{
  InitPush(0);
  PushChar(0);                          // логический номер
  PushChar(0);

  PushChar(4);                          // номер функции

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(5+8, 5+8);

  if (Input() != SER_GOODCHECK) return(0);

  Beep();
  sprintf(szLo+11,"%05u",(uint)0x100*InBuff(3)+InBuff(4));
  return(1);
}

#endif



void    key_SearchBySpeed(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szSearch);
      ShowLo(szBySpeed); DelayMsg(); fKey = 0;

      ibXmax = 0;
      ShowDeviceName(ibXmax);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      enKeyboard = KBD_INPUT1;
      Port();
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTINPUT1;
      ibX = 0;
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibX = GetCharLo(10,11) - 1;
    }


    if (enKeyboard == KBD_POSTINPUT1)
    {
      if (ibX < bPORTS)
      {
        if (ibXmax == 0)
          {  if (StreamPortModem(ibX) == 1) enKeyboard = KBD_SHOW;  }
        else
          {  if (StreamPortDirect(ibX) == 1) enKeyboard = KBD_SHOW;  }
      }
      else Beep();
    }


    if (enKeyboard == KBD_SHOW)
    {
      enKeyboard = KBD_POSTSHOW;
      Clear();

      ibPort = ibX;

      diCurr.ibPort = ibX;
      ShowPortDelayHi(ibPort);

      uchar bRes = 0;                                  // результат операции
      for (ibYmin=bBAUDS; ibYmin>0; ibYmin--)
      {
        mppoPorts[ibX].ibBaud = ibYmin-1;

        for (ibYmax=0; ibYmax<bPARITYS; ibYmax++)
        {
#ifdef NO_DISPLAY
          RunPanel();
#endif

          mppoPorts[ibX].ibParity = ibYmax;

          SetSpeed(ibX);
          ShowSpeeds(ibX,0);

          switch (ibXmax)
          {
            case 0:   if (ChangeSpeedModem() == 1) bRes = 0xEE;  break;

#ifndef SKIP_A
            case 15:
            case 1:   if (ChangeSpeedA() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_B
            case 12:
            case 8:
            case 2:   if (ChangeSpeedB() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_C
            case 3:   if (ChangeSpeedC() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_E
            case 7:
            case 5:   if (ChangeSpeedE() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_F
            case 6:   if (ChangeSpeedF() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_N
            case 19:  if (ChangeSpeedN() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_34
            case 34:  if (ChangeSpeed34() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_38
            case 38:  if (ChangeSpeed38() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_39
            case 39:  if (ChangeSpeed39() == 1) bRes = 0xEE;  break;
#endif
            default:  Error();  return;
          }

          if (fKey == true) { fKey = 0; bRes = 0xFF; }

          if (bRes != 0) break;
        }

        if (bRes != 0) break;
      }

      ShowHi(szSearch);

      if (bRes == 0xFF)
        Stop();
      else if (bRes == 0)
        Error();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibXmax >= bMAXDEVICES+1) ibXmax = 0;
      ShowDeviceName(ibXmax);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibXmax > 0) ibXmax--; else ibXmax = bMAXDEVICES;
      ShowDeviceName(ibXmax);
    }
    else Beep();
  }
  else Beep();
}



#ifndef SKIP_A

bool    ChangeNumberA(void)
{
  InitPush(0);
  PushChar(ibY);
  PushChar(0);                          // тест канала связи

  QueryIO(2+2, 2+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}

#endif



#ifndef SKIP_B

bool    ChangeNumberB(void)
{
  InitPush(0);
  PushChar(ibY);
  PushChar(0);                          // тест канала связи

  QueryIO(2+2, 2+2);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}

#endif



#ifndef SKIP_C

bool    ChangeNumberC(void)
{
  InitPush(0);
  PushChar(ibY);
  PushChar(3);
  PushChar(21);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(3+2+2, 3+3+2);

  if (RevInput() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}

#endif



#ifndef SKIP_E

bool    ChangeNumberE(void)
{
  if (ibY <= 16)
  {
    QueryBreakE();

    InitPush(0);
    PushChar(0x1B);
    PushChar('0'+ibY);

    Query(1+1, 2, 1);

    if (EscInput() != SER_GOODCHECK) return(0);
    Beep();

    return(1);
  }
  else
  {
    bRes = 0xFF;                      // досрочное прекращение цикла
    return(0);
  }
}

#endif



#ifndef SKIP_F

bool    ChangeNumberF(void)
{
  QueryBreakF();

  InitPushPck();
  PushChar(ibY);                        // логический номер
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETLOGICAL);            // номер функции

  PckQueryIO(2+7, 0+7);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}

#endif



#ifndef SKIP_N

bool    ChangeNumberN(void)
{
  InitPush(0);
  PushChar(0);                          // логический номер
  PushChar(ibY);

  PushChar(4);                          // номер функции

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(5+8, 5+8);

  if (Input() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}

#endif



void    key_SearchByNumber(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szSearch);
      ShowLo(szByNumber); DelayMsg(); fKey = 0;

      ibXmax = 1;
      ShowDeviceName(ibXmax);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      enKeyboard = KBD_INPUT1;
      Port();
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTINPUT1;
      ibX = 0;
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibX = GetCharLo(10,11) - 1;
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibYmax = GetCharLo(10,12)) < 255)
        enKeyboard = KBD_SHOW;
      else Beep();
    }


    if (enKeyboard == KBD_POSTINPUT1)
    {
      if (ibX < bPORTS)
      {
        if (StreamPortDirect(ibX) == 1)
          { enKeyboard = KBD_INPUT2;  Address(); }
      }
      else Beep();
    }



    if (enKeyboard == KBD_SHOW)
    {
      enKeyboard = KBD_POSTSHOW;
      Clear();

      diCurr.ibPort  = ibX;

      ibPort = ibX;
      ShowPortDelayHi(ibPort);

      ibYmin = 0;
      for (ibY=ibYmax; ibY<255; ibY++)
      {
#ifdef NO_DISPLAY
        RunPanel();
#endif

        sprintf(szLo+8,"%03u", ibY);

        uchar bRes = 0;                                // результат операции

        switch (ibXmax)
        {
#ifndef SKIP_A
          case 15:
          case 1:   if (ChangeNumberA() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_B
          case 12:
          case 8:
          case 2:   if (ChangeNumberB() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_C
          case 3:   if (ChangeNumberC() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_E
          case 7:
          case 5:   if (ChangeNumberE() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_F
          case 6:   if (ChangeNumberF() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_N
          case 19:  if (ChangeNumberN() == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_34
         case 34:   if (ChangeNumber34(ibY) == 1) bRes = 0xEE;  break;
#endif

#ifndef SKIP_39
         case 39:   if (ChangeNumber39(ibY) == 1) bRes = 0xEE;  break;
#endif

        default:  Error();  return;
        }

        if (bRes == 0xEE)
        {
          sprintf(szLo,"%03u:%-3u", ibY,++ibYmin);
          LongBeep(); DelayMsg();
        }

        if (fKey == true) { fKey = 0; bRes = 0xFF; }

        if (bRes == 0xFF) break;
      }

      ShowHi(szSearch); OK();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,12);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibXmax >= bMAXDEVICES+1) ibXmax = 1;
      ShowDeviceName(ibXmax);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibXmax > 1) ibXmax--; else ibXmax = bMAXDEVICES;
      ShowDeviceName(ibXmax);
    }
    else Beep();
  }
  else Beep();
}

