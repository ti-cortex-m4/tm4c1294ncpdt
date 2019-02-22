/*------------------------------------------------------------------------------
authentication34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../time/delay.h"
#include "crypto34.h"
#include "authentication34.h"



#define MONITOR_34  1



static  uchar           mpbAuthKey[16];
static  uchar           mpbAuthReq[16];



void    QueryAuthKey(void)
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


void    ReadAuthKey(void)
{
  InitPop(3);

  uchar i;
  for (i=0; i<16; i++) {
    mpbAuthKey[i] = PopChar();
  }
}



static void MakeAuthRequest(void)
{
  uchar mpbPass[16];

  memset(&mpbPass, 0, sizeof(mpbPass));

  if (boEnblKeys != true)
  {
    mpbPass[0] = '1';
    mpbPass[1] = '1';
    mpbPass[2] = '1';
    mpbPass[3] = '1';
    mpbPass[4] = '1';
    mpbPass[5] = '1';
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
  MonitorString(" ");

  uchar i;
  for (i=0; i<16; i++)
    MonitorCharHex(mpbPass[i]);
#endif

  uchar mpbRgbKey[16];
  HashMD5(mpbPass, strlen(mpbPass), mpbRgbKey);

#if MONITOR_34
  MonitorString("\n private key ");
  for (i=0; i<16; i++)
    MonitorCharHex(mpbRgbKey[i]);

  MonitorString("\n auth. key ");
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



void    QueryAuthRequest(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x09);
  PushChar(0x12);

  PushIntLtl(1); // уровень доступа: 1,2

  MakeAuthRequest();

  uchar i;
  for (i=0; i<16; i++) {
    PushChar(mpbAuthReq[i]);
  }

  QueryIO(3+3+2, 7+2+16+2);
}


bool    ReadAuthRequest(void)
{
#if MONITOR_34
  MonitorString("\n response [1] ");
  MonitorCharHex(InBuff(1));

  MonitorString("\n response [2] ");
  MonitorCharHex(InBuff(2));
#endif

  return (InBuff(1) & 0x80) == 0;
}



bool    Auth34(void)
{
  DelayOff();
  QueryAuthKey();
  if (Input() != SER_GOODCHECK)
    return 0;
  ReadAuthKey();

  DelayOff();
  QueryAuthRequest();
  if (Input() != SER_GOODCHECK)
    return 0;

  return ReadAuthRequest();
}

