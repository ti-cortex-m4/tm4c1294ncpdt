/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

//#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device39.h"
#include "io39.h"
#include "params39.h"


/*
#define M_PI        3.14159265358979323846



static float        mpeValues[3*7];



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

  PushChar(0x52); // Ô
  PushChar(0x1C);

  Query38(250, 30);
}



float   cosinusDegrees(double  degrees)
{
  return cos(M_PI*degrees/180);
}
*/


float2  ReadParam38(void)
{
  Clear();

  if (fBeginParam == false)
  {

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
//    case PAR_U1 : return GetFloat2(mpeValues[0]/100, true);
//    case PAR_U2 : return GetFloat2(mpeValues[1]/100, true);
//    case PAR_U3 : return GetFloat2(mpeValues[2]/100, true);
//
//    case PAR_I1 : return GetFloat2(mpeValues[3], true);
//    case PAR_I2 : return GetFloat2(mpeValues[4], true);
//    case PAR_I3 : return GetFloat2(mpeValues[5], true);
//
//    case PAR_P1 : return GetFloat2(mpeValues[6], true);
//    case PAR_P2 : return GetFloat2(mpeValues[7], true);
//    case PAR_P3 : return GetFloat2(mpeValues[8], true);
//
//    case PAR_Q1 : return GetFloat2(mpeValues[9], true);
//    case PAR_Q2 : return GetFloat2(mpeValues[10], true);
//    case PAR_Q3 : return GetFloat2(mpeValues[11], true);
//
//    case PAR_S1 : return GetFloat2(mpeValues[12], true);
//    case PAR_S2 : return GetFloat2(mpeValues[13], true);
//    case PAR_S3 : return GetFloat2(mpeValues[14], true);
//
//    case PAR_F1 : return GetFloat2(mpeValues[15]/100, true);
//    case PAR_F2 : return GetFloat2(mpeValues[16]/100, true);
//    case PAR_F3 : return GetFloat2(mpeValues[17]/100, true);
//
//    case PAR_C1 : return GetFloat2(cosinusDegrees(mpeValues[18]/10), true);
//    case PAR_C2 : return GetFloat2(cosinusDegrees(mpeValues[19]/10), true);
//    case PAR_C3 : return GetFloat2(cosinusDegrees(mpeValues[20]/10), true);

    default: return GetFloat2Error();
  }
}
