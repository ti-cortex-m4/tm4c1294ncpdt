/*------------------------------------------------------------------------------
buffer_profile_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include39.h"
#include "buffer_profile_39.h"



#define PROFILE39_SIZE  (6+2)



static profile39    mpBuffPrf39[PROFILE39_SIZE];
static uchar        cbBuffPrfSize39;
static bool         fBuffPrfOveflow39;



void    InitProfile39(void)
{
  memset(&mpBuffPrf39, 0, sizeof(mpBuffPrf39));
  cbBuffPrfSize39 = 0;
  fBuffPrfOveflow39 = false;
}


void    AddProfile39(time  tmTime, uint64_t  ddwValue)
{
  if (cbBuffPrfSize39 < PROFILE39_SIZE)
  {
    uchar i = cbBuffPrfSize39;
    ASSERT(i < PROFILE39_SIZE);
    mpBuffPrf39[i].fExists = true;
    mpBuffPrf39[i].tiTime = tmTime;
    mpBuffPrf39[i].ddwValue = ddwValue;

    cbBuffPrfSize39++;
  }
  else
  {
    fBuffPrfOveflow39 = true;
  }
}



void    MonitorBuffPrf38(void)
{
#ifdef MONITOR_39
  uchar i;
  for (i=0; i<PROFILE39_SIZE; i++)
  {
    profile39 prf = GetProfile39(i);

    MonitorString("\n "); MonitorTime(prf.tiTime);
    MonitorString(" "); MonitorLongDec(prf.ddwValue % 0x100000000);
    MonitorString(" "); MonitorBool(prf.fExists);
  }
#endif
}

void    DeltaProfile39(void)
{
#ifdef MONITOR_39
  MonitorString("\n before");
  MonitorBuffPrf38();
#endif

  bool f = false;

  uchar i;
  for (i=0; i<PROFILE39_SIZE-1; i++)
  {
    profile39 prf1 = GetProfile39(i);
    profile39 prf2 = GetProfile39(i + 1);

    if (prf1.fExists & prf2.fExists)
    {
      mpBuffPrf39[i].tiTime = prf1.tiTime;
      mpBuffPrf39[i].ddwValue = prf2.ddwValue - prf1.ddwValue;
      mpBuffPrf39[i].fExists = true;

      f = true;
    }
    else
    {
      mpBuffPrf39[i].tiTime = tiZero;
      mpBuffPrf39[i].ddwValue = 0;
      mpBuffPrf39[i].fExists = false;
    }
  }

  if (f) cbBuffPrfSize39--;

  i = PROFILE39_SIZE-1;
  mpBuffPrf39[i].tiTime = tiZero;
  mpBuffPrf39[i].ddwValue = 0;
  mpBuffPrf39[i].fExists = false;

#ifdef MONITOR_39
  MonitorString("\n after");
  MonitorBuffPrf38();
  MonitorString("\n finish");
#endif
}


profile39 GetProfile39(uchar  i)
{
  ASSERT(i < PROFILE39_SIZE);
  return mpBuffPrf39[i];
}


uchar   GetProfileSize39(void)
{
  return cbBuffPrfSize39;
}


bool    IsProfileOveflow39(void)
{
  return fBuffPrfOveflow39;
}
