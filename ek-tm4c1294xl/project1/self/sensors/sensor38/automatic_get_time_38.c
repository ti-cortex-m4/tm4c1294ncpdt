/*------------------------------------------------------------------------------
automatic_get_time_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic_get_time_38.h"



void    RunProfile38(void);
void    RunAuth38(void);
void    MakeExtended4T(void);
#include "../../serial/monitor.h"
void    MonitorOpen(uchar  ibPrt);



time2   ReadTimeCan38(void)
{
  MonitorOpen(0);
  Delay(500);
  RunAuth38(); // MakeExtended4T(); //RunAuth38(); // RunProfile38();

  if (1+1 == 2) return GetTime2(tiZero, true);





  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryTime38();
    if (Input38() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTime38();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}
