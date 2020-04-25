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
#include "../../sensors/device_k.h"
#include "../../sensors/device_q.h"
#include "io36.h"
#include "params36_common.h"
#include "params36.h"



extern  bool                    fBeginParam;



void    QueryModel36(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('M');
  PushChar1Bcc('O');
  PushChar1Bcc('D');
  PushChar1Bcc('E');
  PushChar1Bcc('L');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  Query36(1+28+2, n+8+1, 1);
}


ulong2  ReadModel36(void)
{
  InitPop(1);

  return PopLongQ();
}



float2  ReadParam36(void)
{
  Clear();

  if (fBeginParam == false)
  {
    QueryModel36();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ulong2 dw2 = ReadModel36();
    if (dw2.fValid == false) return GetFloat2Error();
    if (dw2.dwValue > 0xFF) return GetFloat2Error();

    uchar bModel = dw2.dwValue;
    bool f1Direction = ((bModel & 0x80) == 0);

    QueryParam36_U123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_U123();

    QueryParam36_I123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_I123();

    if (f1Direction)
    {
      QueryParam36_Pt_1Direction();
      if (Input36() != SER_GOODCHECK) return GetFloat2Error();
      ReadParam36_Pt_1Direction();
    }
    else
    {
      QueryParam36_Pt_2Directions();
      if (Input36() != SER_GOODCHECK) return GetFloat2Error();
      ReadParam36_Pt_2Directions();
    }

    QueryParam36_P123();
    if (Input36() != SER_GOODCHECK) return GetFloat2Error();
    ReadParam36_P123();

    QueryParam36_Ct123();
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
