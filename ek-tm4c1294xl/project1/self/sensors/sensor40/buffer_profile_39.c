/*------------------------------------------------------------------------------
buffer_profile_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include39.h"
#include "error40.h"
#include "buffer_profile_39.h"



#define PROFILE39_SIZE  (6+2)



static profile39    mpProfile39[PROFILE39_SIZE];
static uchar        cbProfileSize39;
static bool         fProfileOveflow39;



void    InitProfile39(void)
{
#ifdef MONITOR_40
  MonitorString("\n init profile ");
#endif

  memset(&mpProfile39, 0, sizeof(mpProfile39));
  cbProfileSize39 = 0;
  fProfileOveflow39 = false;
}


void    AddProfile39(time  tmTime, ulong  mdwValue[4])
{
#ifdef MONITOR_40
  MonitorString("\n add profile "); MonitorIntDec(cbProfileSize39);
  MonitorString(" "); MonitorTime(tmTime);
  MonitorString(" "); MonitorLongDec(mdwValue[0]);
  MonitorString(" "); MonitorLongDec(mdwValue[1]);
  MonitorString(" "); MonitorLongDec(mdwValue[2]);
  MonitorString(" "); MonitorLongDec(mdwValue[3]);
#endif

  if (cbProfileSize39 < PROFILE39_SIZE)
  {
    uchar i = cbProfileSize39;
    ASSERT(i < PROFILE39_SIZE);

    mpProfile39[i].fExists = true;
    mpProfile39[i].tmTime = tmTime;

    uchar c;
    for (c=0; c<4; c++)
      mpProfile39[i].mdwValue[c] = mdwValue[c];

    cbProfileSize39++;
  }
  else
  {
    MonitorString("\n add profile overflow ");
    Error40(160+0);

    fProfileOveflow39 = true;
  }
}



void    MonitorBuffPrf38(void)
{
#ifdef MONITOR_40
  uchar i;
  for (i=0; i<PROFILE39_SIZE; i++)
  {
    profile39 prf = GetProfile39(i);

    MonitorString("\n "); MonitorTime(prf.tmTime);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[0]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[1]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[2]);
    MonitorString(" "); MonitorLongDec(prf.mdwValue[3]);
    MonitorString(" "); MonitorBool(prf.fExists);
  }
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


bool    IsProfileOveflow39(void)
{
  return fProfileOveflow39;
}
