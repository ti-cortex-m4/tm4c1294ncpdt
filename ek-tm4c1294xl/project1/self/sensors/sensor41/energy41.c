/*------------------------------------------------------------------------------
device41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../time/calendar.h"
#include "../../devices/devices_init.h"
#include "../sensor38/io38.h"
#include "../sensor38/dff.h"
#include "../sensor38/device38.h"
#include "energy41.h"



void    QueryEngAbs41(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);
/*
  PushChar(0x02); // A-
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x03); // R+
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x04); // R-
  PushChar(0x02);
  PushChar(0x00);
*/
  Query38(250, 25-9);
}


// значени€ счетчиков на начало суток
void    QueryEngDay41(uchar  ibDayRel)
{
//  MonitorString("\n QueryEngDay41 "); MonitorCharDec(ibDayRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);
/*
  PushChar(0x02); // A-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  PushChar(0x03); // R+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  PushChar(0x04); // R-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);
*/
  Query38(250, 33-15);
}


// значени€ счетчиков на начало мес€ца
void    QueryEngMon41(uchar  ibMonRel)
{
//  MonitorString("\n QueryEngMon41 "); MonitorCharDec(ibMonRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0x09); // A+
  PushChar(0x02);
  PushChar(0x00); // обща€ энерги€
  PushChar(ibMonRel);
  PushChar(ibMonRel);
/*
  PushChar(0x0A); // A-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0B); // R+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0C); // R-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);
*/
  Query38(250, 33-15);
}
