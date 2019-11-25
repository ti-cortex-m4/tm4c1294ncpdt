/*------------------------------------------------------------------------------
STATUS35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals_status.h"
#include "status35.h"



#ifndef SKIP_35

volatile device         deCurr35;

volatile serial         Serial35;



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



void    SetCurr35(device  de)
{
  SetCurr35Internal(de);
  SetCurr(de);
}



void    SetSerial35(serial  se)
{
  Serial35 = se;
}


bool    IsSerial35(void)
{
  return Serial35 == SER_GOODCHECK; // mpSerial[ibPort] == SER_PAUSE;
}

#endif
