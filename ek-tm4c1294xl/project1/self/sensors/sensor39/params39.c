/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../digitals/params/params.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device39.h"
#include "io39.h"
#include "query_params_39.h"
#include "fragment_open_39.h"
#include "params39.h"



// Blue Book: 7.5.1 Value group C codes – Electricity
static const obis_t obisU1      = {1, 0, 32, 7, 0, 255},
                    obisU2      = {1, 0, 52, 7, 0, 255},
                    obisU3      = {1, 0, 72, 7, 0, 255},

                    obisI1      = {1, 0, 31, 7, 0, 255},
                    obisI2      = {1, 0, 51, 7, 0, 255},
                    obisI3      = {1, 0, 71, 7, 0, 255},

                    obisPplus   = {1, 0,  1, 7, 0, 255},
                    obisPminus  = {1, 0,  2, 7, 0, 255},

                    obisQplus   = {1, 0,  3, 7, 0, 255},
                    obisQminus  = {1, 0,  4, 7, 0, 255};




static float        flU1, flU2, flU3,
                    flI1, flI2, flI3,
                    flPplus, flPminus,
                    flQplus, flQminus;



float2  ReadParam39_(void)
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


  fl2 = ReadRegisterWithScaler39(obisPplus, &r);
  if (!fl2.fValid) return GetFloat2Error();
  flPplus = fl2.flValue;

  fl2 = ReadRegisterWithScaler39(obisPminus, &r);
  if (!fl2.fValid) return GetFloat2Error();
  flPminus = fl2.flValue;


  fl2 = ReadRegisterWithScaler39(obisQplus, &r);
  if (!fl2.fValid) return GetFloat2Error();
  flQplus = fl2.flValue;

  fl2 = ReadRegisterWithScaler39(obisQminus, &r);
  if (!fl2.fValid) return GetFloat2Error();
  flQminus = fl2.flValue;


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetFloat2Error();

  return GetFloat2(-1, true);
}



float2  ReadParam39(void)
{
  Clear();

  if (fBeginParam == false)
  {
    if (!ReadParam39_().fValid) return GetFloat2Error();

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

    case PAR_P  : return GetFloat2(flPplus-flPminus, true);

    case PAR_Q  : return GetFloat2(flQplus-flQminus, true);

    case PAR_S  : return GetFloat2(CalcS(flPplus-flPminus, flQplus-flQminus), true);

    default: return GetFloat2Error();
  }
}



#ifdef MONITOR_39

double2 TestParam39(void)
{
  MonitorOpen(0);

  ReadParam39_();

  return GetDouble2(0, true);
}

#endif
