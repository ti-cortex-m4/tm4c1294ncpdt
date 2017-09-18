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
#include "params26.h"



extern  bool                    fBeginParam;



void    ReadParamU1(void)
{
  InitPop(1);

  mpreParam[PAR_I1] = PopDoubleQ()*1000;
  mpreParam[PAR_I2] = PopDoubleQ()*1000;
  mpreParam[PAR_I3] = PopDoubleQ()*1000;
}


void    ReadParamU2(void)
{
  InitPop(1);

  mpreParam[PAR_U1] = PopDoubleQ();
  mpreParam[PAR_U2] = PopDoubleQ();
  mpreParam[PAR_U3] = PopDoubleQ();
}


void    ReadParamU3(void)
{
  InitPop(1);

  mpreParam[PAR_P1] = PopDoubleQ()*1000;
  mpreParam[PAR_P2] = PopDoubleQ()*1000;
  mpreParam[PAR_P3] = PopDoubleQ()*1000;
}


void    ReadParamU4(void)
{
  InitPop(1);

  mpreParam[PAR_F] = PopDoubleQ();
}


bool    ReadParamU(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryCloseU();
    QueryParamU1();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU1();


    QueryCloseU();
    QueryParamU2();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU2();


    QueryCloseU();
    QueryParamU3();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU3();


    QueryCloseU();
    QueryParamU4();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU4();


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : reValue = mpreParam[PAR_P1];  break;
    case PAR_P2 : reValue = mpreParam[PAR_P2];  break;
    case PAR_P3 : reValue = mpreParam[PAR_P3];  break;

    case PAR_I1 : reValue = mpreParam[PAR_I1];  break;
    case PAR_I2 : reValue = mpreParam[PAR_I2];  break;
    case PAR_I3 : reValue = mpreParam[PAR_I3];  break;

    case PAR_U1 : reValue = mpreParam[PAR_U1];  break;
    case PAR_U2 : reValue = mpreParam[PAR_U2];  break;
    case PAR_U3 : reValue = mpreParam[PAR_U3];  break;

    case PAR_F  : reValue = mpreParam[PAR_F];   break;

    default: return(0);
  }

  return(1);
}
