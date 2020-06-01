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
    ibIn++;

    uchar i;
    for (i=0; i<3; i++)
    {

      uint64_t ddw = 0;
      uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
      if (delta == 0xFF) return GetFloat2Error();
      ibIn += delta;

      mpeValues[i] = ddw % 0x100000000;
    }

/*
    ibIn = 10;
    ibIn++;

    uchar b10 = InBuff(10);
    uchar b11 = InBuff(11);
    uchar b12 = InBuff(12);
    uchar b13 = InBuff(13);
    uchar b14 = InBuff(14);
    uchar b15 = InBuff(15);

    uint64_t ddw1 = 0;
    uchar i1 = ibIn;
    uchar delta1 = pucDecodeBitArr((uchar *) &ddw1, InBuffPtr(ibIn));
    if (delta1 == 0xFF) return GetFloat2Error();
    ibIn += delta1;
    ulong dw1 = ddw1 % 0x100000000;

    uint64_t ddw2 = 0;
    uchar i2 = ibIn;
    uchar delta2 = pucDecodeBitArr((uchar *) &ddw2, InBuffPtr(ibIn));
    if (delta2 == 0xFF) return GetFloat2Error();
    ibIn += delta2;
    ulong dw2 = ddw2 % 0x100000000;

    uint64_t ddw3 = 0;
    uchar i3 = ibIn;
    uchar delta3 = pucDecodeBitArr((uchar *) &ddw3, InBuffPtr(ibIn));
    if (delta3 == 0xFF) return GetFloat2Error();
    ibIn += delta3;
    ulong dw3 = ddw3 % 0x100000000;

    uchar i4 = ibIn;
*/
    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat2(mpeValues[0]/100, true);
    case PAR_U2 : return GetFloat2(mpeValues[1]/100, true);
    case PAR_U3 : return GetFloat2(mpeValues[2]/100, true);
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


