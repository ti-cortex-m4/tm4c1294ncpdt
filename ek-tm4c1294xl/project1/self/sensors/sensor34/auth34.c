/*------------------------------------------------------------------------------
auth34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../time/delay.h"
#include "../../display/display.h"
#include "monitor34.h"
#include "auth34.h"
#include "crypto34.h"



//                                          0123456789ABCDEF
static char const       szError4Hi[]     = "  Неправильный  ",
                        szError4Lo[]     = "     пароль     ",
                        szError6Hi[]     = " Несуществующий ",
                        szError6Lo[]     = "уровень доступа ",
                        szError7Hi[]     = "Ключ авторизации",
                        szError7Lo[]     = "    устарел     ",
                        szError8Hi[]     = " Много попыток  ",
                        szError8Lo[]     = "  ввода пароля  ",
                        szErrorHi[]      = "     Ошибка     ",
                        szErrorLo[]      = " авторизации %02X ";



static  uchar           mpbAuthKey[16];
static  uchar           mpbAuthReq[16];



void    QueryAuthKey34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x08);

  QueryIO(3+16+2, 6+2);
}


void    ReadAuthKey34(void)
{
  InitPop(3);

  uchar i;
  for (i=0; i<16; i++) {
    mpbAuthKey[i] = PopChar();
  }
}



static void MakeAuthRequest34(void)
{
  uchar mpbPass[16];

  memset(&mpbPass, 0, sizeof(mpbPass));

  if (boEnblKeys != true)
  {
    mpbPass[0] = '2';
    mpbPass[1] = '2';
    mpbPass[2] = '2';
    mpbPass[3] = '2';
    mpbPass[4] = '2';
    mpbPass[5] = '2';
  }
  else
  {
    line ln = mpphKeys[ibDig];

    uchar i;
    for (i=0; i<bLINE_SIZE; i++)
    {
      if (ln.szLine[i] == 0) break;
      mpbPass[i] = ln.szLine[i];
    }
  }

#if MONITOR_34
  MonitorString("\n password ");
  MonitorIntDec(strlen((char const *)mpbPass));
  MonitorString("    ");

  uchar i;
  for (i=0; i<16; i++)
    MonitorCharHex(mpbPass[i]);
#endif

  uchar mpbRgbKey[16];
  HashMD5((uchar const *)mpbPass, strlen((char const *)mpbPass), mpbRgbKey);

#if MONITOR_34
  MonitorString("\n rgb key       ");
  for (i=0; i<16; i++)
    MonitorCharHex(mpbRgbKey[i]);

  MonitorString("\n auth. key     ");
  for (i=0; i<16; i++)
    MonitorCharHex(mpbAuthKey[i]);
#endif

  EncryptAES(mpbRgbKey, mpbAuthKey, mpbAuthReq);

#if MONITOR_34
  MonitorString("\n auth. request ");
  for (i=0; i<16; i++)
    MonitorCharHex(mpbAuthReq[i]);
#endif
}



void    QueryAuthReq34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x09);
  PushChar(0x12);

  PushIntLtl(2); // уровени доступа: 1,2

  MakeAuthRequest34();

  uchar i;
  for (i=0; i<16; i++) {
    PushChar(mpbAuthReq[i]);
  }

  QueryIO(3+3+2, 7+2+16+2);
}


bool    ReadAuthReq34(void)
{
#if MONITOR_34
  MonitorString("\n auth. request: answer size "); MonitorIntDec(CountInBuff());
  MonitorString("\n in[1] "); MonitorCharHex(InBuff(1));
  MonitorString("\n in[2] "); MonitorCharHex(InBuff(2));
#endif

  if ((CountInBuff() != 8) || ((InBuff(1) & 0x80) != 0)) {
    SaveDisplay();

    switch (InBuff(2)) {
      case 4:  sprintf(szHi, szError4Hi); sprintf(szLo, szError4Lo); break;
      case 6:  sprintf(szHi, szError6Hi); sprintf(szLo, szError6Lo); break;
      case 7:  sprintf(szHi, szError7Hi); sprintf(szLo, szError7Lo); break;
      case 8:  sprintf(szHi, szError8Hi); sprintf(szLo, szError8Lo); break;
      default: sprintf(szHi, szErrorHi);  sprintf(szLo, szErrorLo, InBuff(2)); break;
    }

    Delay(1000);
    LoadDisplay();
  }

  return (InBuff(1) & 0x80) == 0;
}


#if 0

bool    TestAuth34(void)
{
  DelayOff();
  QueryAuthKey34();
  if (Input() != SER_GOODCHECK) return 0;

  ReadAuthKey34();

  DelayOff();
  QueryAuthReq34();
  if (Input() != SER_GOODCHECK) return 0;

  bool b = ReadAuthReq34();

#if MONITOR_34
  MonitorString("\n authentication ");
  MonitorCharDec(b);
#endif

  return b;
}

#endif
