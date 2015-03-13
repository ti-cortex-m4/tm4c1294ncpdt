/*------------------------------------------------------------------------------
AUTOMATIC_B.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../time/delay.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "device_b.h"



bool    QueryOpenB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  return(1);
}



bool    QueryTimeAltB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadTimeAltB();
  return(1);
}

