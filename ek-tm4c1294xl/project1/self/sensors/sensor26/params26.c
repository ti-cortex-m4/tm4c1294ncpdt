/*------------------------------------------------------------------------------
PARAMS26,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_params.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../sensors/device_q.h"
#include "../../sensors/sensor26/device_u.h"
#include "params_u.h"
#include "params26.h"



extern  bool                    fBeginParam;



float2  ReadParamU(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryCloseU();
    QueryParamU_I123();

    if (BccInput() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamU_I123();


    QueryCloseU();
    QueryParamU_U123();

    if (BccInput() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamU_U123();


    QueryCloseU();
    QueryParamU_P123();

    if (BccInput() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamU_P123();


    QueryCloseU();
    QueryParamU_Ft();

    if (BccInput() != SER_GOODCHECK) return GetFloat2Error();
    ReadParamU_Ft();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : return GetFloat2(mpreParam[PAR_P1], true);
    case PAR_P2 : return GetFloat2(mpreParam[PAR_P2], true);
    case PAR_P3 : return GetFloat2(mpreParam[PAR_P3], true);

    case PAR_I1 : return GetFloat2(mpreParam[PAR_I1], true);
    case PAR_I2 : return GetFloat2(mpreParam[PAR_I2], true);
    case PAR_I3 : return GetFloat2(mpreParam[PAR_I3], true);

    case PAR_U1 : return GetFloat2(mpreParam[PAR_U1], true);
    case PAR_U2 : return GetFloat2(mpreParam[PAR_U2], true);
    case PAR_U3 : return GetFloat2(mpreParam[PAR_U3], true);

    case PAR_F  : return GetFloat2(mpreParam[PAR_F], true);

    default: return GetFloat2Error();
  }
}
