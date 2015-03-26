/*------------------------------------------------------------------------------
DEVICES_TIME.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy_spec.h"
#include        "../time/calendar.h"



bool    SearchDefHouIndex(void)
{
  tiAlt = tiDig;
  dwTmp = DateToHouIndex();

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  if (dwTmp > dwBuffC) return(0);

  dwTmp = dwBuffC - dwTmp;
  if (dwTmp > wHOURS) return(0);

  iwDigHou = (wHOURS+iwHardHou-dwTmp) % wHOURS;
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
