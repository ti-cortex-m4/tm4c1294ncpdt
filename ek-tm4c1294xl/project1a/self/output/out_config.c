/*------------------------------------------------------------------------------
OUT_CONFIG,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../flash/flash.h"



void    OutGetConfig(void)
{
  InitPushPtr();

  PushChar(bCANALS);
  PushChar(bGROUPS);
  PushChar(bTARIFFS);
  PushChar(bMINUTES);
  PushIntBig(wHOURS);
  PushChar(bDAYS);
  PushChar(bMONTHS);

  PushChar(0xFF);

  PushIntBig(GetFlashStatus());

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  OutptrOutBuff(16);
}
