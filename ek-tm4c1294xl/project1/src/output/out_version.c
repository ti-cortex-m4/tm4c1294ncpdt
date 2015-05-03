/*------------------------------------------------------------------------------
OUT_VERSION.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../hardware/memory.h"



void    OutVersion(void)
{
uchar i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();
  PushChar(0);
  PushChar(bMAXVERSION);
  PushChar(bMINVERSION);
  PushInt(GetCODEChecksum());
  PushInt(GetBuildNumber());
  PushChar(GetBuildDate_Second());
  PushChar(GetBuildDate_Minute());
  PushChar(GetBuildDate_Hour());
  PushChar(GetBuildDate_Day());
  PushChar(GetBuildDate_Month());
  PushChar(GetBuildDate_Year());
  PushInt(wPrivate);
  PushChar(bLogical);

  PushChar(bCANALS);
  PushChar(bGROUPS);
  PushInt(bMINUTES);
  PushInt(wHOURS);
  PushInt(bDAYS);
  PushInt(bMONTHS);

  Output(100);
}
