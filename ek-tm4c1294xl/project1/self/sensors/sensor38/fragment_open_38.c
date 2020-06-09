/*------------------------------------------------------------------------------
fragment_open_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../serial/monitor.h" // TODO
#include "../../digitals/digitals.h"
#include "device38.h"
//#include "query_profile_38.h"
//#include "query_next_block_38.h"
#include "io38.h"
#include "monitor38.h"
//#include "buffer_y.h"
#include "fragment_open_38.h"



schar   FragmentOpen38(runner38  runner)
{
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return 1;
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return 2;
  DelayOff();

  Query38_Open2(runner.bNS, runner.bNS);
  if (Input38() != SER_GOODCHECK) return 3;
  if (!ValidateIframe(runner.bNS, runner.bNS)) return 4;
  DelayOff();

  runner.bNS++;
  Query38_RR(runner.bNS);
  if (Input38() != SER_GOODCHECK) return 5;
  if (!ValidateSframe(runner.bNS)) return 6;
  DelayOff();

  return 0;
}
