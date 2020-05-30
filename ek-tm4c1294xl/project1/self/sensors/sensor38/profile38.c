/*------------------------------------------------------------------------------
profile38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "profile38.h"



void    QueryProfile38(uchar  ib30min)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); //
  PushChar(0x00);
  PushChar(0xD5); //
  PushChar(0x03);

  PushChar(ib30min);
  PushChar(ib30min);

  Query38(100+20, 17);
}
