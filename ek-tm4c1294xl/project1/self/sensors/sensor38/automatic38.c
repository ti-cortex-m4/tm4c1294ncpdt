/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic38.h"




time2   ReadTimeCan38(void)
{
  QueryTime38();
  if (Input38() != SER_GOODCHECK) return GetTime2Error();
  time ti = ReadTime38();

  return GetTime2(ti, true);
}



double2 ReadCntCurr38(void)
{
  QueryCntCurr38();
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  double db = ReadCntCurr38_() / 1000;

  return GetDouble2(db, true);
}
