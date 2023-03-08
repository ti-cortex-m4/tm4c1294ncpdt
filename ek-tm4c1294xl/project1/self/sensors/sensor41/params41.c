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
  PushChar(0x1C);

  PushChar(0x10); // Q
  PushChar(0x1C);

  PushChar(0x0D); // S
  PushChar(0x1C);

  PushChar(0x1A); // f
  PushChar(0x1C);

  PushChar(0x52); // �
  PushChar(0x1C);

  Query38(250, 46);
}



static float cosinusDegrees(double  degrees)
{
  return cos(M_PI*degrees/180);
}


static void ReadValue41(uchar  *pbIn, uchar  i)
{
  int64_t ddw = 0;
  pbIn = DffDecode(pbIn, &ddw);

  mpeValues[i] = ddw % 0x100000000;
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
    ReadValue41(pbIn, 0);
    ReadValue41(pbIn, 1);
    ReadValue41(pbIn, 2);

    *(pbIn++);
    ReadValue41(pbIn, 3);
    ReadValue41(pbIn, 4);
    ReadValue41(pbIn, 5);

    *(pbIn++);
    ReadValue41(pbIn, 6);
    ReadValue41(pbIn, 7);
    ReadValue41(pbIn, 8);

    *(pbIn++);
    ReadValue41(pbIn, 9);
    ReadValue41(pbIn, 10);
    ReadValue41(pbIn, 11);

    *(pbIn++);
    ReadValue41(pbIn, 12);
    ReadValue41(pbIn, 13);
    ReadValue41(pbIn, 14);

    *(pbIn++);
    ReadValue41(pbIn, 15);
    ReadValue41(pbIn, 16);
    ReadValue41(pbIn, 17);

    *(pbIn++);
    ReadValue41(pbIn, 18);
    ReadValue41(pbIn, 19);
    ReadValue41(pbIn, 20);

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

    case PAR_P1 : return GetFloat2(mpeValues[6], true);
    case PAR_P2 : return GetFloat2(mpeValues[7], true);
    case PAR_P3 : return GetFloat2(mpeValues[8], true);

    case PAR_Q1 : return GetFloat2(mpeValues[9], true);
    case PAR_Q2 : return GetFloat2(mpeValues[10], true);
    case PAR_Q3 : return GetFloat2(mpeValues[11], true);

    case PAR_S1 : return GetFloat2(mpeValues[12], true);
    case PAR_S2 : return GetFloat2(mpeValues[13], true);
    case PAR_S3 : return GetFloat2(mpeValues[14], true);

    case PAR_F1 : return GetFloat2(mpeValues[15]/100, true);
    case PAR_F2 : return GetFloat2(mpeValues[16]/100, true);
    case PAR_F3 : return GetFloat2(mpeValues[17]/100, true);

    case PAR_C1 : return GetFloat2(cosinusDegrees(mpeValues[18]/10), true);
    case PAR_C2 : return GetFloat2(cosinusDegrees(mpeValues[19]/10), true);
    case PAR_C3 : return GetFloat2(cosinusDegrees(mpeValues[20]/10), true);

    default: return GetFloat2Error();
  }
}
