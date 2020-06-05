/*------------------------------------------------------------------------------
time38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "device38.h"
#include "io38.h"
#include "dff.h"
#include "time38.h"



static int32_t          dwCorrectSecond38;



void    SetCorrectSecond38(int64_t  ddw)
{
  dwCorrectSecond38 = ddw;
}



void    QueryCorrect38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x07); // PERFORM_ACTION
  PushChar(0x00);

  PushChar(0x0F); // выполнить коррекцию времени

  uchar n = EncodeInt(dwCorrectSecond38, OutBuffPtr(GetPush()));
  Skip(n);

  Query38(100+18, 14+n);
}


uchar   ReadCorrect38(void)
{
  return InBuff(11);
}



void    QueryManage38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(5); // SET_OPTION
  PushChar(0);

  PushChar(1); // текущее время/дата

  time ti = *GetCurrTimeDate();
  time.bYear -= 12;
  ulong dw = DateToSecIndex(ti);

  uchar n = EncodeInt(dwCorrectSecond38, OutBuffPtr(GetPush()));
  Skip(n);

  Query38(100+18, 14+n);
}



uchar   ReadManage38(void)
{
  return InBuff(11);
}
