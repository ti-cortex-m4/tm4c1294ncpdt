/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "io38.h"
#include "dff.h"
#include "bits2.h"
#include "device38.h"
#include "params38.h"



static float        mpeValues[4];



void    QueryParams38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A);
  PushChar(0x00);

  PushChar(0x18);
  PushChar(0x1C);

  Query38(250, 16);
}



float2  ReadParam38(void)
{
  Clear();

  if (fBeginParam == false)
  {

    QueryParams38();
    if (Input38() != SER_GOODCHECK) return GetFloat2Error();

    uchar ibIn = 10;

    uchar i;
    for (i=0; i<3; i++)
    {
      ibIn++;

      uint64_t ddw = 0;
      uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
      if (delta == 0xFF) return GetFloat2Error();
      ibIn += delta;

      mpeValues[i] = ddw % 0x100000000;
    }

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat2(mpeValues[0], true);
    case PAR_U2 : return GetFloat2(mpeValues[1], true);
    case PAR_U3 : return GetFloat2(mpeValues[2], true);
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


