/*------------------------------------------------------------------------------
STATUS35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals_status.h"
#include "status35.h"



volatile device         deCurr35;

volatile serial         Serial35;



void    SetCurr35Internal(device  de)
{
  deCurr35 = de;
//  MonitorString("\t set pause: "); MonitorIntHex(deCurr35);
}


device  GetCurr35Internal(void)
{
//  MonitorString("\t get pause: "); MonitorIntHex(deCurr35);
  return deCurr35;
}



void    SetCurr35(device  de)
{
  SetCurr35Internal(de);
  SetCurr(de);
  SetSerial35(SER_OVERFLOW);
}



void    SetSerial35(serial  se)
{
  Serial35 = se;
}


bool    IsSerial35(void)
{
  return Serial35 == SER_GOODCHECK; // mpSerial[ibPort] == SER_PAUSE;
}
