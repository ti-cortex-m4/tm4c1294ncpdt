/*------------------------------------------------------------------------------
OUT_CONFIG,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../flash/at45.h"



void    OutGetConfig(void)
{
  InitPushPtr();

  PushChar(bCANALS);
  PushChar(bGROUPS);
  PushChar(bTARIFFS);
  PushChar(bMINUTES);
  PushInt(wHOURS);
  PushChar(bDAYS);
  PushChar(bMONTHS);

  PushChar(0xFF);

  PushInt(GetFlashStatus());

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  OutptrOutBuff(16);
}
