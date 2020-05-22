/*------------------------------------------------------------------------------
device38.c

Ёнергомера CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "device38.h"



void    QueryTime38(void)
{
  InitPush(0);

  PushChar(0x06);
  PushChar(0xE8);
  PushChar(0xB7);
  PushChar(0xC4);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x06);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x34);
  PushChar(0xEA);

  Query38(16, 12);
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
