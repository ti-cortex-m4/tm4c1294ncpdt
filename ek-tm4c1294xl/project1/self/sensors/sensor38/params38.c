/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "params38.h"



float2  ReadParam38(void)
{
  Clear();

  if (fBeginParam == false)
  {

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat2(-1, true);
    case PAR_U2 : return GetFloat2(-1, true);
    case PAR_U3 : return GetFloat2(-1, true);
    case PAR_U  : return GetFloat2(-1, true);

    case PAR_I1 : return GetFloat2(-1, true);
    case PAR_I2 : return GetFloat2(-1, true);
    case PAR_I3 : return GetFloat2(-1, true);
    case PAR_I  : return GetFloat2(-1, true);

    case PAR_P1 : return GetFloat2(-1, true);
    case PAR_P2 : return GetFloat2(-1, true);
    case PAR_P3 : return GetFloat2(-1, true);
    case PAR_P  : return GetFloat2(-1, true);

    case PAR_Q1 : return GetFloat2(-1, true);
    case PAR_Q2 : return GetFloat2(-1, true);
    case PAR_Q3 : return GetFloat2(-1, true);
    case PAR_Q  : return GetFloat2(-1, true);

    case PAR_S1 : return GetFloat2(-1, true);
    case PAR_S2 : return GetFloat2(-1, true);
    case PAR_S3 : return GetFloat2(-1, true);
    case PAR_S  : return GetFloat2(-1, true);

    case PAR_F1 : return GetFloat2(-1, true);
    case PAR_F2 : return GetFloat2(-1, true);
    case PAR_F3 : return GetFloat2(-1, true);
    case PAR_F  : return GetFloat2(-1, true);

    case PAR_C1 : return GetFloat2(-1, true);
    case PAR_C2 : return GetFloat2(-1, true);
    case PAR_C3 : return GetFloat2(-1, true);
    case PAR_C  : return GetFloat2(-1, true);

    default: return GetFloat2Error();
  }
}


