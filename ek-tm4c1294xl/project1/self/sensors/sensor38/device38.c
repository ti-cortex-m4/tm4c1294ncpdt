/*------------------------------------------------------------------------------
device38.c

Энергомера CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "device38.h"



void    PushAddress38(void)
{
    PushChar(0xE8);
    PushChar(0xB7);
    PushChar(0xC4);
    PushChar(0x04);

//  PushLongLtl(80001000); // TODO
}


void    QueryTime38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x01);

  Query38(100+18, 14);
}


time    ReadTime38(void)
{
  time ti;

  ti.bSecond = 0;
  ti.bMinute = 0;
  ti.bHour   = 0;

  ti.bDay    = 0;
  ti.bMonth  = 0;
  ti.bYear   = 0;

  return ti;
}
