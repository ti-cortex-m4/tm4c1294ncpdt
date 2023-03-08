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

  BeforeAddress41();
  PushAddress41();
  AfterAddress41();

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


uchar*  ReadValue41(uchar  *pbIn, uchar  i)
{
  int64_t ddw = 0;
  pbIn = DffDecode(pbIn, &ddw);

  mpeValues[i] = ddw % 0x100000000;
  return pbIn;
}


uchar*  ReadValuePositive41(uchar  *pbIn, uchar  i)
{
  int64_t ddw = 0;
  pbIn = DffDecodePositive(pbIn, &ddw);

  mpeValues[i] = ddw % 0x100000000;
  return pbIn;
}


float2  ReadParam41(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryParams41();
    if (Input38() != SER_GOODCHECK) return GetFloat2Error();

    uchar* pbIn = InBuffPtr(16);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 0); // U
    pbIn = ReadValue41(pbIn, 1);
    pbIn = ReadValue41(pbIn, 2);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 3); // I
    pbIn = ReadValue41(pbIn, 4);
    pbIn = ReadValue41(pbIn, 5);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 6); // P
    pbIn = ReadValue41(pbIn, 7);
    pbIn = ReadValue41(pbIn, 8);
    pbIn = ReadValue41(pbIn, 9);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 10); // Q
    pbIn = ReadValue41(pbIn, 11);
    pbIn = ReadValue41(pbIn, 12);
    pbIn = ReadValue41(pbIn, 13);

    *(pbIn++);
    pbIn = ReadValuePositive41(pbIn, 14); // S
    pbIn = ReadValuePositive41(pbIn, 15);
    pbIn = ReadValuePositive41(pbIn, 16);
    pbIn = ReadValuePositive41(pbIn, 17);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 18); // f
    pbIn = ReadValue41(pbIn, 19);
    pbIn = ReadValue41(pbIn, 20);

    *(pbIn++);
    pbIn = ReadValue41(pbIn, 21); // Ô
    pbIn = ReadValue41(pbIn, 22);
    pbIn = ReadValue41(pbIn, 23);

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
