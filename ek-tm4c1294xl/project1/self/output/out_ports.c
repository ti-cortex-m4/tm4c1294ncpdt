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
    PushIntBig(mpwMinorInDelay[i]);
    PushLongBig(GetMinorDelay(i));
  }

  for (i=0; i<bPORTS; i++) {
    PushIntBig(mpwMajorInDelay[i]);
    PushLongBig(GetMajorDelay(i));
  }

  for (i=0; i<bPORTS; i++)
    PushChar(mpSerial[i]);

  for (i=0; i<bPORTS; i++)
    PushBool(mpboLocal[i]);

  for (i=0; i<bPORTS; i++)
    PushBool(mpboLocalDisable[i]);

  PushIntBig(GetCurr());
  PushIntBig(GetPause());
  PushIntBig(GetNext());

  PushChar(1);

  PushChar(bPortsStatus);

  PushChar(bInputModeReset);
  PushTime(tiInputModeReset);
  PushLongBig(dwInputModeReset);

  Output(100);
}



void    OutOutputDelay(void)
{
  InitPushCRC();

  uchar p;
  for (p=0; p<bPORTS; p++)
    PushIntBig(mpwOutputDelay[p]);

  Output(sizeof(mpwOutputDelay));
}
