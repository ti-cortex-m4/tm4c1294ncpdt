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
#include "device34.h"
#include "auth34.h"
#include "crypto34.h"



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
  MonitorIntDec(strlen(mpbPass));
  MonitorString("    ");

  uchar i;
  for (i=0; i<16; i++)
    MonitorCharHex(mpbPass[i]);
#endif

  uchar mpbRgbKey[16];
  HashMD5(mpbPass, strlen(mpbPass), mpbRgbKey);

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


bool    ReadAuthReq(void)
{
#if MONITOR_34
  MonitorString("\n response [1] ");
  MonitorCharHex(InBuff(1));

  MonitorString("\n response [2] ");
  MonitorCharHex(InBuff(2));
#endif

  return (InBuff(1) & 0x80) == 0;
}


#if 1

bool    TestAuth34(void)
{
  DelayOff();
  QueryAuthKey34();
  if (Input() != SER_GOODCHECK)
    return 0;

  ReadAuthKey34();

  DelayOff();
  QueryAuthReq34();
  if (Input() != SER_GOODCHECK)
    return 0;

  bool b = ReadAuthReq();

#if MONITOR_34
  MonitorString("\n result ");
  MonitorCharDec(b);
#endif

  return b;
}

#endif
