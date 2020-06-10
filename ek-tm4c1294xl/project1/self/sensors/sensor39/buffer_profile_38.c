/*------------------------------------------------------------------------------
buffer_profile_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "buffer_profile_38.h"



#define PROFILE39_SIZE  (6+1)



static profile39    mpBuffPrf39[PROFILE39_SIZE];
static uchar        cbBuffPrfSize39;
static bool         fBuffPrfOveflow39;



void    InitBuffPrf38(void)
{
  memset(&mpBuffPrf39, 0, sizeof(mpBuffPrf39));
  cbBuffPrfSize39 = 0;
  fBuffPrfOveflow39 = false;
}


void    AddBuffPrf38(time  tiTime, uint64_t  ddwValue)
{
  if (cbBuffPrfSize39 < PROFILE39_SIZE)
  {
    uchar i = cbBuffPrfSize39;
    ASSERT(i < PROFILE39_SIZE);
    mpBuffPrf39[i].fExists = true;
    mpBuffPrf39[i].tiTime = tiTime;
    mpBuffPrf39[i].ddwValue = ddwValue;

    cbBuffPrfSize39++;
  }
  else
  {
    fBuffPrfOveflow39 = true;
  }
}



void    DeltaBuffPrf38(void)
{
#ifdef MONITOR_39
  MonitorString("\n Before DeltaBuffPrf38 ");

  uchar i;
  for (i=0; i<PROFILE39_SIZE; i++)
  {
    profile39 prf = GetBuffPrf38(i);

    MonitorString("\n "); MonitorTime(prf.tiTime);
    MonitorString(" "); MonitorLongDec(prf.ddwValue % 0x100000000);
    MonitorString(" "); MonitorBool(prf.fExists);
  }
#endif

#ifdef MONITOR_39
  MonitorString("\n After DeltaBuffPrf38 ");

  for (i=0; i<PROFILE39_SIZE-1; i++)
  {
    profile39 prf = GetBuffPrf38(i);

    MonitorString("\n "); MonitorTime(prf.tiTime);
    MonitorString(" "); MonitorLongDec(prf.ddwValue % 0x100000000);
    MonitorString(" "); MonitorBool(prf.fExists);
  }
#endif
}


profile39 GetBuffPrf38(uchar  i)
{
  ASSERT(i < PROFILE39_SIZE);
  return mpBuffPrf39[i];
}


uchar   GetBuffPrfSize38(void)
{
  return cbBuffPrfSize39;
}


bool    GetBuffPrfOveflow38(void)
{
  return fBuffPrfOveflow39;
}
