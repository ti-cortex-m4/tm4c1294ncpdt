/*------------------------------------------------------------------------------
OUT_PORTS!C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../digitals/sensors.h"
#include "../digitals/digitals_status.h"
#include "../serial/ports.h"



void    OutPorts(void)
{
uchar i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  for (i=0; i<bPORTS; i++)
    Push(&mppoPorts[i], sizeof(port));

  for (i=0; i<bPORTS; i++) {
    PushInt(mpwMinorInDelay[i]);
    PushLong(GetMinorDelay(i));
  }

  for (i=0; i<bPORTS; i++) {
    PushInt(mpwMajorInDelay[i]);
    PushLong(GetMajorDelay(i));
  }

  for (i=0; i<bPORTS; i++)
    PushChar(mpSerial[i]);

  for (i=0; i<bPORTS; i++)
    PushBool(mpboLocal[i]);

  for (i=0; i<bPORTS; i++)
    PushBool(mpboLocalDisable[i]);

  PushInt(GetCurr());
  PushInt(GetPause());
  PushInt(GetNext());

  PushChar(1);

  PushChar(bPortsStatus);

  PushChar(bInputModeReset);
  PushTime(tiInputModeReset);
  PushLong(dwInputModeReset);

  Output(100);
}



void    OutOutputDelay(void)
{
  InitPushCRC();

  uchar p;
  for (p=0; p<bPORTS; p++)
    PushInt(mpwOutputDelay[p]);

  Output(sizeof(mpwOutputDelay));
}
