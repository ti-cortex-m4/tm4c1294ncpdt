/*------------------------------------------------------------------------------
DEVICES_TIME.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_profile.h"
#include        "../time/calendar.h"



bool    SearchDefHouIndex(time  tiExt)
{
  ulong dwExt = DateToHouIndex(tiExt);
  ulong dwInt = DateToHouIndex(tiCurr);

  if (dwExt > dwInt) return(0);

  ulong dwT = dwInt - dwExt;
  if (dwT > wHOURS) return(0);

  iwDigHou = (wHOURS+iwHardHou-dwT) % wHOURS;
  return(1);
}


#ifdef  DAYS100

bool    SearchDefHouIndex2(uint  wLimit)
{
  tiAlt = tiDig;
  dwTmp = DateToHouIndex();

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  if (dwTmp > dwBuffC) return(0);
  if (dwBuffC - dwTmp > wHOURS) return(0);

  if (dwTmpPrev == 0)
  {
    dwTmpPrev = dwTmp;
  }
  else
  {
    if (dwTmp > dwTmpPrev) return(0);
    if (dwTmpPrev - dwTmp > wLimit) return(0);
    dwTmpPrev = dwTmp;
  }

  iwDigHou = (wHOURS+iwHardHou-(dwBuffC-dwTmp)) % wHOURS;
  return(1);
}

#endif
