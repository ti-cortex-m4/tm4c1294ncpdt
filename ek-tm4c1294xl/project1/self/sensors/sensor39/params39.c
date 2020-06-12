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



static const obis_t obisU1 = {1, 0, 32, 7, 0, 255};
static const obis_t obisU2 = {1, 0, 52, 7, 0, 255};
static const obis_t obisU3 = {1, 0, 72, 7, 0, 255};

static const obis_t obisI1 = {1, 0, 31, 7, 0, 255};
static const obis_t obisI2 = {1, 0, 51, 7, 0, 255};
static const obis_t obisI3 = {1, 0, 71, 7, 0, 255};



static float        flU1, flU2, flU3;
static float        flI1, flI2, flI3;



float2  ReadValue39(const obis_t  obis, runner39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryParam39_(obis, (*pr).bNS, (*pr).bNR, (*pr).bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetFloat2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetFloat2Error();
  float fl = ReadType18ULong16(); // TODO определять тип автоматически
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


    float2 fl2 = ReadValue39(obisU1, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU1 = fl2.flValue / 10;

    fl2 = ReadValue39(obisU2, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU2 = fl2.flValue / 10;

    fl2 = ReadValue39(obisU3, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU3 = fl2.flValue / 10;


    fl2 = ReadValue39(obisI1, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI1 = fl2.flValue * 10; // TODO читать коэффициенты автоматически

    fl2 = ReadValue39(obisI2, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI2 = fl2.flValue * 10;

    fl2 = ReadValue39(obisI3, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI3 = fl2.flValue * 10;


    Query38_DISC();
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
    DelayOff();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat2(flU1, true);
    case PAR_U2 : return GetFloat2(flU2, true);
    case PAR_U3 : return GetFloat2(flU3, true);

    case PAR_I1 : return GetFloat2(flI1, true);
    case PAR_I2 : return GetFloat2(flI2, true);
    case PAR_I3 : return GetFloat2(flI3, true);

    default: return GetFloat2Error();
  }
}
