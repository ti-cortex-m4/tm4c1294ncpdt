/*------------------------------------------------------------------------------
buffer_profile_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include39.h"
#include "buffer_profile_39.h"



#define PROFILE39_SIZE  (6+2)



static profile39    mpProfile39[PROFILE39_SIZE];
static uchar        cbProfileSize39;
static bool         fProfileOveflow39;



void    InitProfile39(void)
{
  memset(&mpProfile39, 0, sizeof(mpProfile39));
  cbProfileSize39 = 0;
  fProfileOveflow39 = false;
}


void    AddProfile39(time  tmTime, uint64_t  ddwValue)
{
  if (cbProfileSize39 < PROFILE39_SIZE)
  {
    uchar i = cbProfileSize39;
    ASSERT(i < PROFILE39_SIZE);
    mpProfile39[i].fExists = true;
    mpProfile39[i].tmTime = tmTime;
    mpProfile39[i].ddwValue = ddwValue;

    cbProfileSize39++;
  }
  else
  {
    fProfileOveflow39 = true;
  }
}



void    MonitorBuffPrf38(void)
{
#ifdef MONITOR_39
  uchar i;
  for (i=0; i<PROFILE39_SIZE; i++)
  {
    profile39 prf = GetProfile39(i);

    MonitorString("\n "); MonitorTime(prf.tmTime);
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
      mpProfile39[i].tmTime = prf1.tmTime;
      mpProfile39[i].ddwValue = prf2.ddwValue - prf1.ddwValue;
      mpProfile39[i].fExists = true;

      f = true;
    }
    else
    {
      mpProfile39[i].tmTime = tiZero;
      mpProfile39[i].ddwValue = 0;
      mpProfile39[i].fExists = false;
    }
  }

  if (f) cbProfileSize39--;

  i = PROFILE39_SIZE-1;
  mpProfile39[i].tmTime = tiZero;
  mpProfile39[i].ddwValue = 0;
  mpProfile39[i].fExists = false;

#ifdef MONITOR_39
  MonitorString("\n after");
  MonitorBuffPrf38();
  MonitorString("\n finish");
#endif
}


profile39 GetProfile39(uchar  i)
{
  ASSERT(i < PROFILE39_SIZE);
  return mpProfile39[i];
}


uchar   GetProfileSize39(void)
{
  return cbProfileSize39;
}


bool    IsProfileOveflow39(void) // TODO use IsProfileOveflow39
{
  return fProfileOveflow39;
}
