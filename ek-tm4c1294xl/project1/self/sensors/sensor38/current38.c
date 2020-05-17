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
#include "monitor38.h"
#include "device38.h"
#include "query_engabs_38.h"
#include "current38.h"



uchar                   bNS;
uchar                   bNR;
uchar                   bInvokeId;



void    Query38_Open2_Current(void)
{
  bNS = 0;
  bNR = 0;
  bInvokeId = 0;

  Query38_Open2(bNS, bNR);
}


void    Query38_RR_Current(void)
{
  bNR++;
  Query38_RR(bNR);
}


void    QueryEngAbs38_Current(void)
{
  bNS++;
  QueryEngAbs38(bNS, bNR, bInvokeId++);
}



bool    ValidateSframe_Current(void)
{
  return ValidateSframe(bNR);
}


bool    ValidateIframe_Current(void)
{
  return ValidateIframe(bNS, bNR);
};



void    SaveCurrent38(void)
{
}

void    ReadCurrent38(void)
{
}
