/*------------------------------------------------------------------------------
time41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/rtc.h"
#include "../../time/calendar.h"
#include "device41.h"
#include "../sensor38/io38.h"
#include "../sensor38/dff.h"
#include "time41.h"



//static int32_t          dwCorrectSecond38;



time    SecondsToTime41(ulong  dw)
{
  time ti = SecIndexToDate(dw);
  ti.bYear += 12;
  return ti;
}


ulong   TimeToSeconds41(time  ti)
{
  ti.bYear -= 12;
  return DateToSecIndex(ti);
}



void    QueryTime41(void)
{
  InitPush(0);

  BeforeAddress41();
  PushAddress41();
  AfterAddress41();

  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x01);

  Query38(250, 33);
}


time    ReadTime41(void)
{
  int64_t ddw = 0;
  DffDecodePositive(InBuffPtr(17), &ddw);
  return SecondsToTime41(ddw % 0x100000000);
}


/*
void    SetCorrectSecond41(int64_t  ddw)
{
  dwCorrectSecond38 = ddw;
}



void    QueryCorrect41(void)
{
//  MonitorString("\n QueryCorrect38 ");

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x07); // PERFORM_ACTION
  PushChar(0x00);

  PushChar(0x0F); // выполнить коррекцию времени

  uchar n = Encode41(dwCorrectSecond38, OutBuffPtr(GetPush()));
  Skip(n);

  Query38(100+18, 14+n);
}


uchar   ReadCorrect41(void)
{
  return InBuff(11);
}



void    QueryManage41(void)
{
//  MonitorString("\n QueryManage38 ");

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(5); // SET_OPTION
  PushChar(0);
  PushChar(1); // текущее время/дата

  ulong dw = TimeToSeconds41(*GetCurrTimeDate());

  uchar n = Encode41(dw, OutBuffPtr(GetPush()));
  Skip(n);

  Query38(100+18, 14+n);
}



uchar   ReadManage41(void)
{
  return InBuff(11);
}
*/
