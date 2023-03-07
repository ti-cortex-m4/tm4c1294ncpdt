/*------------------------------------------------------------------------------
params41.c


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device41.h"
#include "../sensor38/io38.h"
#include "../sensor38/dff.h"
#include "params41.h"



#define M_PI        3.14159265358979323846



static float        mpeValues[24];



void    QueryParams41(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x05);

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x05);
  PushChar(0x01);

  PushAddress41();

  PushChar(0x04);
  PushChar(0x02);
  PushChar(0x80);
  PushChar(0x05);
  PushChar(0x02);
  PushChar(0x81);
  PushChar(0x04);
  PushChar(0x02);
  PushChar(0x84);
  PushChar(0x8D);
  PushChar(0x02);
  PushChar(0x83);
  PushChar(0x7F);

  PushChar(0x0A);
  PushChar(0x00);

  PushChar(0x18); // U
  PushChar(0x1C);

  PushChar(0x16); // I
  PushChar(0x1C);

  PushChar(0x0E); // P
  PushChar(0x1E);

  PushChar(0x10); // Q
  PushChar(0x1E);

  PushChar(0x0D); // S
  PushChar(0x1E);

  PushChar(0x1A); // f
  PushChar(0x1C);

  PushChar(0x52); // Ô
  PushChar(0x1C);

  Query38(250, 46);
}



static float cosinusDegrees(double  degrees)
{
  return cos(M_PI*degrees/180);
}


static void Read41(uchar  *pbIn, uchar  ibStart, uchar  bSize)
{
  *(pbIn++);

  uchar i;
  for (i=0; i<bSize; i++)
  {
    int64_t ddw = 0;
    pbIn = DffDecode(pbIn, &ddw);

    mpeValues[ibStart+i] = ddw % 0x100000000;
  }
}


float2  ReadParam41(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryParams41();
    if (Input38() != SER_GOODCHECK) return GetFloat2Error();

    uchar* pbIn = InBuffPtr(16);

    Read41(pbIn, 0, 3);
    Read41(pbIn, 3, 3);
    Read41(pbIn, 6, 4);
    Read41(pbIn, 10, 4);
    Read41(pbIn, 14, 4);
    Read41(pbIn, 18, 3);
    Read41(pbIn, 21, 3);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat2(mpeValues[0]/100, true);
    case PAR_U2 : return GetFloat2(mpeValues[1]/100, true);
    case PAR_U3 : return GetFloat2(mpeValues[2]/100, true);

    case PAR_I1 : return GetFloat2(mpeValues[3], true);
    case PAR_I2 : return GetFloat2(mpeValues[4], true);
    case PAR_I3 : return GetFloat2(mpeValues[5], true);

    case PAR_P  : return GetFloat2(mpeValues[6], true);
    case PAR_P1 : return GetFloat2(mpeValues[7], true);
    case PAR_P2 : return GetFloat2(mpeValues[8], true);
    case PAR_P3 : return GetFloat2(mpeValues[9], true);

    case PAR_Q  : return GetFloat2(mpeValues[10], true);
    case PAR_Q1 : return GetFloat2(mpeValues[11], true);
    case PAR_Q2 : return GetFloat2(mpeValues[12], true);
    case PAR_Q3 : return GetFloat2(mpeValues[13], true);

    case PAR_S  : return GetFloat2(mpeValues[14], true);
    case PAR_S1 : return GetFloat2(mpeValues[15], true);
    case PAR_S2 : return GetFloat2(mpeValues[16], true);
    case PAR_S3 : return GetFloat2(mpeValues[17], true);

    case PAR_F1 : return GetFloat2(mpeValues[18]/100, true);
    case PAR_F2 : return GetFloat2(mpeValues[19]/100, true);
    case PAR_F3 : return GetFloat2(mpeValues[20]/100, true);

    case PAR_C1 : return GetFloat2(cosinusDegrees(mpeValues[21]/10), true);
    case PAR_C2 : return GetFloat2(cosinusDegrees(mpeValues[22]/10), true);
    case PAR_C3 : return GetFloat2(cosinusDegrees(mpeValues[23]/10), true);

    default: return GetFloat2Error();
  }
}
