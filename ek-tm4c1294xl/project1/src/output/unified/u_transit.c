/*------------------------------------------------------------------------------
U_TRANSIT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_uni.h"
#include        "../../memory/mem_flow.h"
#include        "../../include/queries_uni.h"
#include        "../../digitals/wait_query.h"
#include        "../../serial/ports.h"
#include        "../../serial/flow.h"
#include        "response_uni.h"
#include        "u_config.h"
#include        "u_transit.h"



static void SetFlowUni(uchar  ibPort)
{
  ibFlowPortTo = ibPort+1;
  cbMaxFlowDelay = bInBuff9;
}



static void ResultFlowUni(void)
{
  time ti = tiCurr;
  ti.bSecond = bUNI_GOODTRANSIT;

  Output2_Code(0, bUNI_GOODTRANSIT, &ti);
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
    digital di = mpdiDevicesUni[bInBuff7-1];
    if ((di.ibPort != 2) && (di.ibPort != 3))
      Result2_Info(bUNI_BADDATA,3);
    else
    {
      if (cbWaitQuery != 0)
        Result2(bUNI_BADTRANSIT);
      else if (ibPort == 0) 
      {
        SetFlowUni(di.ibPort);
        RunFlow0();
        ResultFlowUni();
      }
      else if (ibPort == 1)
      {
        SetFlowUni(di.ibPort);
        RunFlow1();
        ResultFlowUni();
      } 
      else
        Result2_Info(bUNI_BADDATA,4);
    }
  }
}
