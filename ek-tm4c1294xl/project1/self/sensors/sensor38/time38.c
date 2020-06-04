/*------------------------------------------------------------------------------
time38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../display/messages.h"
//#include "../../time/delay.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
//#include "../../digitals/current/current_run.h"
//#include "dff.h"
#include "io38.h"
#include "time38.h"



void    QueryCorrect38(void)
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

