/*------------------------------------------------------------------------------
MODEMS!C


------------------------------------------------------------------------------*/

#include    "../main.h"
#include    "../memory/mem_ports.h"
#include    "../memory/mem_digitals.h"
#include    "../memory/mem_phones.h"
#include    "../display/display.h"
#include    "../keyboard/keyboard.h"
#include    "../keyboard/time/key_timedate.h"
#include    "../time/delay.h"
#include    "../flash/records.h"
#include    "../digitals/digitals.h"
#include    "../digitals/digitals_pause.h"
#include    "../devices/devices.h"
#include    "../digitals/digitals_messages.h"
#include    "../digitals/digitals_display.h"
#include    "ports.h"
#include    "ports_common.h"
#include    "ports_devices.h"
#include    "ports_modems.h"
#include    "speeds_display.h"
#include    "flow.h"
#include    "monitor.h"
#include    "modems.h"



//                                         0123456789ABCDEF
static char const       szBaud[]        = "   модем ...    ",
                        szCommon[]      = " настройки 1 ...",
                        szCustom[]      = " настройки 2 ...",
                        szRing[]        = "      ring      ",
                        szNoCarrier[]   = "   no carrier   ",
                        szModemError[]  = "      error     ",
                        szNoDialtone[]  = "  no dialtone   ",
                        szBusy[]        = "    занято !    ",
                        szNoAnswer[]    = "    no answer   ",
                        szEscape[]      = "     +++ ...    ",
                        szHookOff[]     = " отключение ... ",
                        szDTROff[]      = "     сброс !    ",
                        szBreakConnect[]= " перекоммутация ",
                        szBlockingAll[] = " без соединения ",
                        szConnect[]     = "   соединение   ",
                        szDisconnect[]  = "  отсоединение  ",
                        szNoConnect[]   = " нет соединения ",
                        szNoDisconnect[]= "нет отсоединения";



// принудительный разрыв connect при действии/бездействии клавиатуры
void    KeyBreakConnect(void)
{
  if (fConnect == 1)
  {
    ShowHi(szPause);
    ShowLo(szModemStop);

    fSlide = 0;
    DelayMsg();
  }
  else Stop();

  enKeyboard = KBD_BEGIN;
  wProgram = 0;

  fKeyOn = 1;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_KEYBREAK);
}



uchar   GetModemAnswer(void)
{
uchar   i,j;
uchar   w;

  if ((IndexInBuff() >= 2) && (IndexInBuff() <= 4))
  {
    w = 0;
    for (i=0; i<IndexInBuff()-1; i++)
    {
      j = InBuff(i);
      if ((j >= '0') && (j <= '9'))
        w = w*10 + ToChar(j);
      else
      {
        w = 0xFF;
        break;
      }
    }
  }
  else w = 0xFE;

  if (w < 0x100)
    return(w);
  else
    return(0xFD);
}



void    QueryModemBaud(bool fShow)
{
  if (fShow == 1) ShowLo(szBaud);

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 2+2, 1);
}


void    QueryModemCommon(bool fShow)
{
  if (fShow == 1) ShowLo(szCommon);

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('E');                        // E0 - локальное эхо выключено
  PushChar('0');

  PushChar('V');                        // V0 - вывод сообщений в числовом формате
  PushChar('0');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 6+2, 1);
}


void    QueryModemCustom(void)
{
  ShowLo(szCustom); //DelayInf();

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('Q');                        // Q0 - возвращать ответы при выполнениии команды
  PushChar('0');

  PushChar('X');
  PushChar('4');

  PushChar('&');                        // &D3 - разрыв связи и выполнение сброса изменении сигнала DTR
  PushChar('D');
  PushChar('2');

  PushChar(0x5C);                       // \Q0 - управление потоком запрещено
  PushChar('Q');
  PushChar('0');

  PushChar('S');                        // S0=2 - подъём телефонной трубки на втором гудке
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 16+2, 1);
}



void    QueryModemConnect(void)
{
  HideCurrTime(0);

  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('D');
  PushChar('P');

  line ph = mpphPhones[diCurr.ibPhone - 1];

  Clear();
  strcpy(szLo, ph.szLine);

  uchar i;
  for (i=0; i<bLINE_SIZE; i++)
  {
    if ( ph.szLine[i] == 0 ) break;
    PushChar( ph.szLine[i] );
  }

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 4+i+2, 1);
}



bool    ShowModemConnect(void)
{
  bool fAlt = 0;

  switch ( GetModemAnswer() )
  {
    case 2:  ShowLo(szRing);        break;
    case 3:  ShowLo(szNoCarrier);   break;
    case 4:  ShowLo(szModemError);  break;
    case 6:  ShowLo(szNoDialtone);  break;
    case 7:  ShowLo(szBusy);        break;
    case 8:  ShowLo(szNoAnswer);    break;

    case 0xFF:
    case 0xFE:
    case 0xFD: Clear(); sprintf(szLo+3,"ошибка: %u", GetModemAnswer());
                                    break;

    default:   Clear(); sprintf(szLo+1,"соединение: %u", GetModemAnswer());
               fAlt = 1;            break;
  }

  DelayInf();
  return(fAlt);
}


void    QueryModemEscape(void)
{
  ShowLo(szEscape); //DelayInf();

  Delay(1500);

  InitPush(0);

  PushChar('+');
  PushChar('+');
  PushChar('+');

  Query(SERIAL_MODEM, 3, 1);

  Delay(1500);
}


void    QueryModemHookOff(void)
{
  ShowLo(szHookOff); //DelayInf();

  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('H');
  PushChar('0');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 4+2, 1);
}



void    ModemDTROff(void)
{
  ShowLo(szDTROff); //DelayInf();

//  DTROff();
}



void    RunLocal(void)
{
  if (mpSerial[ibPort] == SER_LOCAL)
  {
    if (mpboLocalDisable[ibPort] == true)
      mpSerial[ibPort] = SER_BEGIN;
    else
    {
      InitPush(0);

      PushChar('O');
      PushChar('K');
      PushChar('\r');
      PushChar('\n');

      Query(SERIAL_LOCAL, 2+2, 1);
    }
  }
}


void    RunLocal_All(void)
{
  ibPort = 0;
  RunLocal();

  ibPort = 1;
  RunLocal();

  ibPort = 2;
  RunLocal();

  ibPort = 3;
  RunLocal();
}


// соединение с каналом (требует установки diCurr)
bool    Connect(void)
{
uchar   i;

  fConnect = 0;

  ibPort = diCurr.ibPort;

  if (StreamPort(diCurr.ibPort) == 0) return(0);
  if (diCurr.ibPhone == 0) return(1);

  if (mpboEnblCan[ibDig] == false) { ShowLo(szBlockingAll); DelayInf(); return(1); }

  ShowPort(diCurr.ibPort);
  ShowLo(szConnect); DelayInf();

  for (i=0; i<MaxRepeatsFixed(); i++)
  {
//    QueResult(bRES_MODEMBAUD, i);

    DelayOff();
    QueryModemBaud(1);

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeatsFixed()) ;
  else
    { ShowLo(szBaudOK); DelayInf(); mpcwBaud[diCurr.ibPort]++; }


  for (i=0; i<MaxRepeatsFixed(); i++)
  {
//    QueResult(bRES_MODEMCOMMON, i);

    DelayOff();
    QueryModemCommon(1);

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);

    if (i > 0)                          // переход из состояния hook on
    {
      DelayOff();
      QueryModemEscape();

      if (ModInputOK(3) == 1) ;
      if (fKey == true) return(0);

      DelayOff();
      QueryModemHookOff();

      if (ModInputOK(1) == 1) ;
      if (fKey == true) return(0);
    }
  }

  if (i == MaxRepeatsFixed()) return(0);
  ShowLo(szCommonOK); DelayInf(); mpcwCommon[diCurr.ibPort]++;


  if (boCustomModem == true)
  {
    for (i=0; i<MaxRepeatsFixed(); i++)
    {
//      QueResult(bRES_MODEMCUSTOM, i);

      DelayOff();
      QueryModemCustom();

      if (ModInputOK(1) == 1) break;
      if (fKey == true) return(0);
    }

    if (i == MaxRepeatsFixed()) return(0);
    ShowLo(szCustomOK); DelayInf(); mpcwCustom[diCurr.ibPort]++;
  }


  for (i=0; i<MaxRepeatsFixed(); i++)
  {
//    QueResult(bRES_MODEMCONNECT, i);

    DelayOff();

    fConnect = 1;
    QueryModemConnect();

    if ((ModInput(bMaxConnect,1) == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1)) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeatsFixed()) return(0);


  cbWaitOnline = 0;

  mpcwConnect[diCurr.ibPort]++;
  return(1);
}


// требует установки diCurr
bool    SafeConnect(void)
{
#ifdef  FLOW
  CloseFlow();
#endif

  SaveDisplay();
  bool fAlt = Connect();
  LoadDisplay();

//  QueResult(bRES_CONNECT, (uchar)fAlt);
//  ResetAllSerial();

  return(fAlt);
}



// разъединение с каналом (требует установки diCurr)
bool    Disconnect(void)
{
uchar   i;
bool    fResult;

  fResult = 0;

  ibPort = diCurr.ibPort;

  ShowPort(diCurr.ibPort);
  ShowLo(szDisconnect); DelayInf();

  for (i=0; i<MaxRepeatsFixed(); i++)
  {
    // переход из состояния hook on
//    QueResult(bRES_MODEMESCAPE, i);

    DelayOff();
    QueryModemEscape();

    if (ModInputOK(3) == 1) break;
    if (fKey == true) return(0);

    // переход из состояния hook off
//    QueResult(bRES_MODEMHOOKOFF, i);

    DelayOff();
    QueryModemHookOff();

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeatsFixed()) ;
  else
    { ShowLo(szEscapeOK); DelayInf(); mpcwEscape[diCurr.ibPort]++; }


  for (i=0; i<MaxRepeatsFixed(); i++)
  {
//    QueResult(bRES_MODEMHOOKOFF, i);

    DelayOff();
    QueryModemHookOff();

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeatsFixed()) ;
  else
  {
    fResult = 1;
    ShowLo(szHookOffOK); DelayInf(); mpcwHookOff[diCurr.ibPort]++;
  }


  ModemDTROff();
  mpcwDTROff[diCurr.ibPort]++;

  fConnect = 0;

  return(fResult);
}


// требует установки diCurr
bool    SafeDisconnect(void)
{
#ifdef  FLOW
  CloseFlow();
#endif

  SaveDisplay();
  bool fAlt = Disconnect();
  LoadDisplay();

//  QueResult(bRES_DISCONNECT, (uchar)fAlt);
//  ResetAllSerial();

  return(fAlt);
}



void    InitConnect(void)
{
  diLast.ibPort  = 0xFF;
  diLast.ibPhone = 0xFF;

//  ResetAllSerial();
}


void    InitConnectKey(void)
{
  InitConnect(); //fQuery = 0;
}

/*
void    InitConnectQue(void)
{
  InitConnect(); fQuery = 1;
  ibPortQue = ibPort;
}


void    DoneConnectQue(void)
{
  ibPort = ibPortQue;
  DelayMsg();
}
*/


// требует установки diCurr
bool    BreakConnect(void)
{
	bool fAlt = ((diLast.ibPort != diCurr.ibPort) || (diLast.ibPhone != diCurr.ibPhone));

  if (fAlt == 1)
  {
    SaveDisplay();

    ShowPort(diCurr.ibPort);
    ShowLo(szBreakConnect); DelayInf();

    LoadDisplay();
  }

//  QueResult(bRES_BREAKCONNECT, (uchar)fAlt);
  return(fAlt);
}


// провека необходимости разъединения с каналом (требует установки diCurr)
bool    NeedDisconnect(void)
{
  if (diCurr.ibPhone == 0)
    return(diCurr.bDevice != 0);
  else
    return(1);
}



// требует установки diCurr
bool    LoadConnect(uchar  ibCanal)
{
  if (fConnect == 1)
  {
    if ((diLast.ibPort == 0xFF) || (diLast.ibPhone == 0xFF))
    {
      KeyBreakConnect();
      return(0);
    }
    else if (BreakConnect() == 1)
    {
      if (NeedDisconnect() == 1)
      {
        diNext = diCurr; diCurr = diLast;
        bool fAlt = SafeDisconnect();
        diCurr = diNext;

        if (fAlt == 0) { ShowLo(szNoDisconnect); InitConnect(); return(0); }
      }

      ibDig = ibCanal;
      if (SafeConnect() == 0) { ShowLo(szNoConnect);  InitConnect(); return(0); }
    }
    else ibDig = ibCanal;
  }
  else
  {
    ibDig = ibCanal;
    if (SafeConnect() == 0) { ShowLo(szNoConnect);  InitConnect(); return(0); }
  }

  return(1);
}


// требует установки diCurr
void    SaveConnect(void)
{
  diLast = diCurr;
}



uchar   GetNextDigitalIdx()
{
  uchar c;
  for (c=ibDig; c<bCANALS; c++)
  {
    MonitorString("\n c="); MonitorIntDec(c);
    if (CompareLines(ibDig,c) == true)
    {
      MonitorString("\n the same digital, skip");
      continue;
    } else {
      MonitorString("\n the next digital");
      return c;
    }
  }

  MonitorString("\n no next digital");
  return 0xFF;
}


bool    IsModemDisconnect(void)
{
  bool fConnected = (diCurr.ibPhone != 0) && (fConnect == 1); // есть соединение ?

  if (!fConnected)
  {
    MonitorString("\n no connection - disconnect");
    return false; // нет соединения - не разъединять
  }
  else
  {
    uchar c = GetNextDigitalIdx();
    if (c == 0xFF) {
      MonitorString("\n connection, no next digital - disconnect");
      return true; // есть соединение и последний канал - разъединять
    }

    if( (GetDigitalPort(ibDig)  == GetDigitalPort(c))    &&
        (GetDigitalPhone(ibDig) == GetDigitalPhone(c)) ) {
      MonitorString("\n connection, the same port/phone - no disconnect");
      return false; // есть соединение и следующий счетчик на том же самом порту и телефоне - не разъединять
    } else {
      MonitorString("\n connection, another port/phone - disconnect");
      return true; // есть соединение и следующий счетчик не на том же самом порту или телефоне - разъединять
    }
  }
}

