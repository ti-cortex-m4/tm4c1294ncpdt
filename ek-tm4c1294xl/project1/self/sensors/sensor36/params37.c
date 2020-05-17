/*------------------------------------------------------------------------------
PARAMS37,C

CE303 NNCL2
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_params.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../digitals/params/params.h"
#include "io36.h"
#include "params36_common.h"
#include "params37.h"



extern  bool                    fBeginParam;



float2  ReadParam37(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryParam36_U123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_U123();

    QueryParam36_I123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_I123();

    QueryParam36_Pt_2Directions();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_Pt_2Directions();

    QueryParam36_P123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_P123();

    QueryParam36_Qt();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_Qt();

    QueryParam36_Q123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_Q123();

    mpreParam[PAR_S] = CalcS(mpreParam[PAR_P], mpreParam[PAR_Q]);
    mpreParam[PAR_S1] = CalcS(mpreParam[PAR_P1], mpreParam[PAR_Q1]);
    mpreParam[PAR_S2] = CalcS(mpreParam[PAR_P2], mpreParam[PAR_Q2]);
    mpreParam[PAR_S3] = CalcS(mpreParam[PAR_P3], mpreParam[PAR_Q3]);

    QueryParam36_Ct123();
    if (Input36() != SER_GOODCHECK)
    {
      mpreParam[PAR_C] = CalcC(mpreParam[PAR_P], mpreParam[PAR_Q]);
      mpreParam[PAR_C1] = CalcC(mpreParam[PAR_P1], mpreParam[PAR_Q1]);
      mpreParam[PAR_C2] = CalcC(mpreParam[PAR_P2], mpreParam[PAR_Q2]);
      mpreParam[PAR_C3] = CalcC(mpreParam[PAR_P3], mpreParam[PAR_Q3]);
    }
    else
      ReadParam36_Ct123();

    QueryParam36_Ft();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_Ft();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P  : return GetFloat2(mpreParam[PAR_P], true);
    case PAR_P1 : return GetFloat2(mpreParam[PAR_P1], true);
    case PAR_P2 : return GetFloat2(mpreParam[PAR_P2], true);
    case PAR_P3 : return GetFloat2(mpreParam[PAR_P3], true);

    case PAR_Q  : return GetFloat2(mpreParam[PAR_Q], true);
    case PAR_Q1 : return GetFloat2(mpreParam[PAR_Q1], true);
    case PAR_Q2 : return GetFloat2(mpreParam[PAR_Q2], true);
    case PAR_Q3 : return GetFloat2(mpreParam[PAR_Q3], true);

    case PAR_S  : return GetFloat2(mpreParam[PAR_S], true);
    case PAR_S1 : return GetFloat2(mpreParam[PAR_S1], true);
    case PAR_S2 : return GetFloat2(mpreParam[PAR_S2], true);
    case PAR_S3 : return GetFloat2(mpreParam[PAR_S3], true);

    case PAR_U1 : return GetFloat2(mpreParam[PAR_U1], true);
    case PAR_U2 : return GetFloat2(mpreParam[PAR_U2], true);
    case PAR_U3 : return GetFloat2(mpreParam[PAR_U3], true);

    case PAR_I1 : return GetFloat2(mpreParam[PAR_I1], true);
    case PAR_I2 : return GetFloat2(mpreParam[PAR_I2], true);
    case PAR_I3 : return GetFloat2(mpreParam[PAR_I3], true);

    case PAR_C :  return GetFloat2(mpreParam[PAR_C], true);
    case PAR_C1 : return GetFloat2(mpreParam[PAR_C1], true);
    case PAR_C2 : return GetFloat2(mpreParam[PAR_C2], true);
    case PAR_C3 : return GetFloat2(mpreParam[PAR_C3], true);

    case PAR_F  : return GetFloat2(mpreParam[PAR_F], true);

    default: return GetFloat2Error();
  }
}
