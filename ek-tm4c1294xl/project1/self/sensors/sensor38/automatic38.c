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





double2 temp(void)
{
  QueryEngAbs38(0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEng38(11);


  QueryEngDay38(0,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);

  QueryEngDay38(1,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);

  QueryEngDay38(2,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);


  QueryEngMon38(0,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);

  QueryEngMon38(1,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);

  QueryEngMon38(2,0);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  ReadEngStatus38(11);

  return GetDouble2Error();
}


