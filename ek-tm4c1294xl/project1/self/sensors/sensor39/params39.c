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
#include "device39.h"
#include "io39.h"
#include "query_params_39.h"
#include "params39.h"



static const obis_t U3 = {1, 0, 72, 7, 0, 255};



static float        reU3;



float2  ReadValue39(const obis_t  obis, runner39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryParam39_(obis, (*pr).bNS, (*pr).bNR, (*pr).bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetFloat2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetFloat2Error();
  float fl = ReadParam39_() / 10;
  DelayOff();

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetFloat2Error();
  if (!ValidateSframe((*pr).bNR)) return GetFloat2Error();
  DelayOff();

  return GetFloat2(fl, true);
}



float2  ReadParam39(void)
{
  Clear();

  if (fBeginParam == false)
  {
    Query38_DISC();
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    DelayOff();

    Query38_SNRM();
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    DelayOff();


    runner39 r = InitRunner();


    Query38_Open2(r.bNS, r.bNR);
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    if (!ValidateIframe(r.bNS, r.bNR)) return GetFloat2Error();
    DelayOff();

    r.bNR++;
    Query38_RR(r.bNR);
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    if (!ValidateSframe(r.bNR)) return GetFloat2Error();
    DelayOff();


    float2 fl2 = ReadValue39(U3, &r);
    if (!fl2.fValid) return GetFloat2Error();
    reU3 = fl2.flValue;


    Query38_DISC();
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    DelayOff();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
//    case PAR_U1 : return GetFloat2(mpeValues[0]/100, true);
//    case PAR_U2 : return GetFloat2(mpeValues[1]/100, true);
    case PAR_U3 : return GetFloat2(reU3, true);

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
