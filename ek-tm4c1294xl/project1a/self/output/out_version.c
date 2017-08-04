/*------------------------------------------------------------------------------
OUT_VERSION,C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../hardware/memory.h"
#include "../include/flash.h"
#include "out_version.h"



void    OutVersion(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushChar(0);
  PushChar(bMAXVERSION);
  PushChar(bMINVERSION);
  PushIntBig(GetRomChecksum());
  PushIntBig(GetBuildNumber());
  PushChar(GetBuildDate_Second());
  PushChar(GetBuildDate_Minute());
  PushChar(GetBuildDate_Hour());
  PushChar(GetBuildDate_Day());
  PushChar(GetBuildDate_Month());
  PushChar(GetBuildDate_Year());
  PushIntBig(wPrivate);
  PushChar(bLogical);

  PushChar(bCANALS);
  PushChar(bGROUPS);
  PushIntBig(bMINUTES);
  PushIntBig(wHOURS);
  PushIntBig(bDAYS);
  PushIntBig(bMONTHS);

  PushIntBig(wPAGE_BYTES);
  PushIntBig(wLEAF_BYTES);
  PushIntBig(wPAGES_TOTAL);
  PushIntBig(FLASH_BEGIN);
  PushIntBig(FLASH_END);

  Output(100);
}
