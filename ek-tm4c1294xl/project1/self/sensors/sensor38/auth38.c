/*------------------------------------------------------------------------------
auth38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "hash38.h"
#include "auth38.h"



#include "../../memory/mem_serial3.h"
int EncodeInt(int64_t value, uint8_t *send_buffer_position);

typedef union
{
  float         fdwBuff;
  uchar         mbBuff[4];
  ulong         dwBuff;
  long          dwsBuff;
} combo1;



void    QueryAuthRequest38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(6); // GET_INFO
  PushChar(0x00);

  PushChar(24); // 0x18

  Query38(250, 14);
}


ulong   ReadAuthRequest38(void)
{
  uint64_t ddw = 0;
  pucDecodeBitArr((uchar *) &ddw, InBuffPtr(10+1));

  return ddw % 0x100000000;
}



void    QueryAuthResponse38(ulong  random)
{
  uchar password[16+1];
  password[0] = '0';
  password[1] = 0;

  uchar password_size = 1;

  ulong dw = Hash38(&password[0], password_size, random);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(7); // ?
  PushChar(0);
  PushChar(1);

  int n = EncodeInt(dw, OutBuffPtr(11));
  MonitorString("n="); MonitorCharDec(n);

  *OutBuffPtr(11+n-1) |= 0x80;

  InitPush(11+n);
  PushChar(0xF1);
  PushChar(0x04);

//  MonitorOut(250, 11+n+2);
/*
  combo1   coTemp;
  coTemp.dwBuff = Hash38(&password[0], password_size, random);
  PushChar(coTemp.mbBuff[0]);
  PushChar(coTemp.mbBuff[1]);
  PushChar(coTemp.mbBuff[2]);
  PushChar(coTemp.mbBuff[3]);

  PushChar(0x3F); // 999999 сек
  PushChar(0x42);
  PushChar(0x0F);
  PushChar(0x00);
/ *
  mbOut485[7] = coTemp.mbBuff[3];
  mbOut485[6] = coTemp.mbBuff[2];
  mbOut485[5] = coTemp.mbBuff[1];
  mbOut485[4] = coTemp.mbBuff[0];

  //Время = 999999 сек. (такое значение посылал AdminTools)
  mbOut485[8]  = 0x3F;
  mbOut485[9]  = 0x42;
  mbOut485[10] = 0x0F;
  mbOut485[11] = 0x00;
/ *
  uchar n = EncodeInt(OutBuffPtr(11), dw);

  InitPush(11 + n);

  PushChar(0x3F); // 999999 сек
  PushChar(0x42);
  PushChar(0x0F);
  PushChar(0x00);
* /
*/
  Query38(250, 11+n+3);

}


uchar   ReadAuthResponse38(void)
{
  return InBuff(11);
}



#ifdef MONITOR_38

void    RunAuth38(void)
{
    ulong out;
    int64_t ddw;
    uchar n;

    ddw = 1;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 10;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 100;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 1000;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);


    ddw = -1;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -10;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -100;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1000;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);



    ddw = 1;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 10;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 100;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 1000;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);


    ddw = -1;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -10;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -100;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1000;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);




  QueryAuthRequest38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  ulong dwRandom = ReadAuthRequest38();
  MonitorString("\n random="); MonitorLongHex(dwRandom);

  QueryAuthResponse38(dwRandom);
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

  uchar b = ReadAuthResponse38();
  MonitorString("authorization="); MonitorCharDec(b);
}

#endif
