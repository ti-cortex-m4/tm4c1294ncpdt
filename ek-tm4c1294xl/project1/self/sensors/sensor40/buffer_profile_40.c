/*------------------------------------------------------------------------------
buffer_profile_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include40.h"
#include "error40.h"
#include "buffer_profile_40.h"



#define PROFILE40_SIZE  (6+6)



static profile40    mpProfile[PROFILE40_SIZE];

static uchar        cbProfileSize;
static bool         fProfileOveflow;



void    InitProfile40(void)
{
#ifdef MONITOR_40
  MonitorString("\n InitProfile40");
#endif

  memset(&mpProfile, 0, sizeof(mpProfile));

  cbProfileSize = 0;
  fProfileOveflow = false;
}


void    AddProfile40(time  tmHhrEnd, ulong  mdwValue[4])
{
#ifdef MONITOR_40
  MonitorString("\n AddProfile40 (period end time)");
  MonitorString(" "); MonitorIntDec(cbProfileSize);
  MonitorString(" "); MonitorTime(tmHhrEnd);
  MonitorString(" "); MonitorLongDec(mdwValue[0]);
  MonitorString(" "); MonitorLongDec(mdwValue[1]);
  MonitorString(" "); MonitorLongDec(mdwValue[2]);
  MonitorString(" "); MonitorLongDec(mdwValue[3]);
#endif

  if (cbProfileSize < PROFILE40_SIZE)
  {
    uchar p = cbProfileSize;
    ASSERT(p < PROFILE40_SIZE);

    mpProfile[p].fExists = true;
    mpProfile[p].tmHhrEnd = tmHhrEnd;

    uchar i;
    for (i=0; i<4; i++)
      mpProfile[p].mdwValue[i] = mdwValue[i];

    cbProfileSize++;
  }
  else
  {
#ifdef MONITOR_40
    MonitorString("\n overflow !");
#endif

    Error40(160+0);
    fProfileOveflow = true;
  }
}



void    MonitorProfile40(void)
{
#ifdef MONITOR_40
  uchar p;
  for (p=0; p<PROFILE40_SIZE; p++)
  {
    profile40 prf = GetProfile40(p);

    MonitorString("\n "); MonitorTime(prf.tmHhrEnd);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[0]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[1]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[2]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[3]);
    MonitorString(" "); MonitorBool(prf.fExists);
  }
#endif
}


profile40 GetProfile40(uchar  p)
{
  ASSERT(p < PROFILE40_SIZE);
  return mpProfile[p];
}


uchar   GetProfileSize40(void)
{
  return cbProfileSize;
}


bool    IsProfileOveflow40(void)
{
  return fProfileOveflow;
}
