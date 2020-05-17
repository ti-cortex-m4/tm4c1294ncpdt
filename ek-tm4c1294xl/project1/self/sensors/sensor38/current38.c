/*------------------------------------------------------------------------------
current38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../serial/ports.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
//#include "../../digitals/current/current_run.h"
#include "io38.h"
#include "device_38.h"
#include "current38.h"


  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;



void    Query38_Open2_Current(void)
{
  bNS = 0;
  bNR = 0;
  bInvokeId = 0;

  Query38_Open2(bNS, bNR);
}



void    Query38_RR_Current(void)
{
  Query38_RR(bNR);
}



void    QueryEngAbs38_Current(void)
{
  QueryEngAbs38(bNS, bNR, bInvokeId++);
}



void    ValidateSframe_Current(void)
{
  ValidateSframe(bNR);
}



void    ValidateIframe_Current(void)
{
  ValidateIframe(bNS, bNR);
);
