/*------------------------------------------------------------------------------
PARAMS36,C

яе301 NNCL2
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_params.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "io36.h"
#include "params_x.h"
#include "params36.h"



extern  bool                    fBeginParam;



float2  ReadParam36(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryModelU();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ulong2 dw2 = ReadModelU();
    if (dw2.fValid == false) return GetFloat2Error();
    if (dw2.dwValue > 0xFF) return GetFloat2Error();

    uchar bModel = dw2.dwValue;
    bool f1Direction = ((bModel & 0x80) == 0);

    QueryParamX_U123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamX_U123();

    QueryParamX_I123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamX_I123();

    if (f1Direction)
    {
      QueryParamX_Pt_1Direction();
      if (Input36() != SER_GOODCHECK) return GetFloat2Error();
      ReadParamX_Pt_1Direction();
    }
    else
    {
      QueryParamX_Pt_2Directions();
      if (Input36() != SER_GOODCHECK) return GetFloat2Error();
      ReadParamX_Pt_2Directions();
    }

    QueryParamX_P123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamX_P123();

    QueryParamX_Ct123();
    if (Input36() != SER_GOODCHECK)
    {
      combo32 co;
      co.dwBuff = MAX_LONG;

      mpreParam[PAR_C] = co.flBuff;
      mpreParam[PAR_C1] = co.flBuff;
      mpreParam[PAR_C2] = co.flBuff;
      mpreParam[PAR_C3] = co.flBuff;
    }
    else
      ReadParamX_Ct123();

    QueryParamX_Ft();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamX_Ft();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P  : return GetFloat2(mpreParam[PAR_P], true);
    case PAR_P1 : return GetFloat2(mpreParam[PAR_P1], true);
    case PAR_P2 : return GetFloat2(mpreParam[PAR_P2], true);
    case PAR_P3 : return GetFloat2(mpreParam[PAR_P3], true);

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
