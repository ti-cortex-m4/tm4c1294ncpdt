/*------------------------------------------------------------------------------
STATUS35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "status35.h"



#ifndef SKIP_35

volatile device         deCurr35;



void    SetCurr35Internal(device  de)
{
  deCurr35 = de;
  MonitorString("\n set pause: "); MonitorIntHex(deCurr35);
}


device  GetCurr35Internal(void)
{
  MonitorString("\n get pause: "); MonitorIntHex(deCurr35);
  return deCurr35;
}

#endif
