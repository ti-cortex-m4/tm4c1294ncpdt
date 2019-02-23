/*------------------------------------------------------------------------------
time34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "unix_time_gmt34.h"
#include "device34.h"
#include "time34.h"



static time             tmCurr34;
static int32_t          dwCorrectSecond;



void    SetTimeCurr34(time tm)
{
  tmCurr34 = tm;
}


time    GetTimeCurr34(void)
{
  return tmCurr34;
}


uchar   GetTimeCurrIndex34(void)
{
  return tmCurr34.bHour*2 + tmCurr34.bMinute/30;
}


void    QueryTime34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}


time    ReadTime34(void)
{
  InitPop(3);
  return UnixTimeToTimeFromGMT34(PopLongLtl());
}



void    SetCorrectSecond34(int32_t dw)
{
    dwCorrectSecond = dw;
}


void    QueryCorrect34(void)
{
#if MONITOR_34
  MonitorString("\n query time correct");
#endif

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x4F);
  PushChar(0x00);
  PushChar(0x04);
  PushChar(0x08);

  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);

  PushLongLtl(dwCorrectSecond);

  QueryIO(3+3+2, 7+4+4+2);
}


void    ReadCorrect34(void)
{
  if ((CountInBuff() != 8) || ((InBuff(1) & 0x80) != 0)) {
    SaveDisplay();

    sprintf(szHi,"Ошибка коррекции");
    Clear();
    sprintf(szLo+2,"времени: %02X",InBuff(2));

    Delay(1000);
    LoadDisplay();
  }
}



void    QueryManage34(void)
{
#if MONITOR_34
  MonitorString("\n query time manage");
#endif

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x04);
  PushChar(0x08);

  PushLongLtl(TimeToUnixTimeToGMT34(tiCurr));

  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);

  QueryIO(3+3+2, 7+4+4+2);
}


void    ReadManage34(void)
{
  if ((CountInBuff() != 8) || ((InBuff(1) & 0x80) != 0)) {
    SaveDisplay();

    sprintf(szHi,"Ошибка установки");
    Clear();
    sprintf(szLo+2,"времени: %02X",InBuff(2));

    Delay(1000);
    LoadDisplay();
  }
}
