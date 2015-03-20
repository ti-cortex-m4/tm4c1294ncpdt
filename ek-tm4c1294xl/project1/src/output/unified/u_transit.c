/*------------------------------------------------------------------------------
U_TRANSIT.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "queries2.h"
#include        "postinput2.h"
#include        "ports.h"
#include        "flow.h"
#include        "u_config.h"



#ifndef MODBUS

void    SetFlowUni(void)
{
  ibPortTo = diT.ibPort+1;
  cbMaxFlowDelay = bInBuff9;
}



void    ResultFlowUni(void)
{
  tiAlt = tiCurr;
  tiAlt.bSecond = bUNI_GOODTRANSIT;

  Output2_Code(0, bUNI_GOODTRANSIT, &tiAlt);
}



void    GetTransitUni(void)
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2_Info(bUNI_BADDATA,1);
  else if (bInBuff7 > cbDevicesUni)
    Result2_Info(bUNI_BADDATA,2);
  else
  {
    diT = mpdiDevicesUni[bInBuff7-1];
    if ((diT.ibPort != 2) && (diT.ibPort != 3))
      Result2_Info(bUNI_BADDATA,3);
    else
    {
      if (cbWaitQuery != 0)
        Result2(bUNI_BADTRANSIT);
      else if (ibPort == 0) 
      {
        SetFlowUni();
        RunFlow0();
        ResultFlowUni();
      }
      else if (ibPort == 1)
      {
        SetFlowUni();
        RunFlow1();
        ResultFlowUni();
      } 
      else
        Result2_Info(bUNI_BADDATA,4);
    }
  }
}

#endif
*/
