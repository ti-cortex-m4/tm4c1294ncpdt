/*------------------------------------------------------------------------------
params34.c


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
#include "device39.h"
#include "io39.h"
#include "query_params_39.h"
#include "fragment_open_39.h"
#include "params39.h"



static const obis_t obisU1 = {1, 0, 32, 7, 0, 255},
                    obisU2 = {1, 0, 52, 7, 0, 255},
                    obisU3 = {1, 0, 72, 7, 0, 255},

                    obisI1 = {1, 0, 31, 7, 0, 255},
                    obisI2 = {1, 0, 51, 7, 0, 255},
                    obisI3 = {1, 0, 71, 7, 0, 255};



static float        flU1, flU2, flU3,
                    flI1, flI2, flI3;



double2 ReadValue39(const obis_t  obis, runner39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryGetRegisterValueDLMS(obis, (*pr));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetDouble2Error();
  ulong2 dw2 = ReadValueX();
  if (!dw2.fValid) return GetDouble2Error();
//  DelayOff();

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe((*pr).bNR)) return GetDouble2Error();
//  DelayOff();

  return GetDouble2(dw2.dwValue, true);
}



double2 ReadScaler39(const obis_t  obis, runner39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryGetRegisterScalerDLMS(obis, (*pr));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetDouble2Error();
  schar2 sc2 = ReadRegisterScaler();
  if (!sc2.fValid) return GetDouble2Error();
//  DelayOff();

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe((*pr).bNR)) return GetDouble2Error();
//  DelayOff();

  double db = pow(10, sc2.bValue);
  return GetDouble2(db, true);
}



float2  ReadRegisterWithScaler39(const obis_t  obis, runner39*  pr)
{
  double2 value = ReadValue39(obis, pr);
  if (!value.fValid) return GetFloat2Error();

  double2 scaler = ReadScaler39(obis, pr);
  if (!scaler.fValid) return GetFloat2Error();

  return GetFloat2(value.dbValue * scaler.dbValue, true);
}



float2  ReadParam39(void)
{
  Clear();

  if (fBeginParam == false)
  {
    runner39 r = InitRunner();
    FragmentOpen39(&r);


    float2 fl2;

    fl2 = ReadRegisterWithScaler39(obisU1, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU1 = fl2.flValue;

    fl2 = ReadRegisterWithScaler39(obisU2, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU2 = fl2.flValue;

    fl2 = ReadRegisterWithScaler39(obisU3, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flU3 = fl2.flValue;


    fl2 = ReadRegisterWithScaler39(obisI1, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI1 = fl2.flValue*1000;

    fl2 = ReadRegisterWithScaler39(obisI2, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI2 = fl2.flValue*1000;

    fl2 = ReadRegisterWithScaler39(obisI3, &r);
    if (!fl2.fValid) return GetFloat2Error();
    flI3 = fl2.flValue*1000;


    Query38_DISC();
    if (Input39() != SER_GOODCHECK) return GetFloat2Error();
//    DelayOff();


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
