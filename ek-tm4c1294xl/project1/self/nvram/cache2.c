/*------------------------------------------------------------------------------
CACHE2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "cache.h"
#include "cache2.h"



void    SaveCacheBool(cache const  *pch, bool  fVal)
{
  bool *pfVal = (bool *) pch->pbBuff;
  *pfVal = fVal;

  SaveCache(pch);
}


void    LoadCacheBool(cache const  *pch, bool  fDef)
{
  LoadCache(pch);
  bool *pfVal = (bool *) pch->pbBuff;

  if (!((*pfVal == true) || (*pfVal == false)))
  {
    *pfVal = fDef;
    SaveCache(pch);
  }
}


void    LoadCacheChar(cache const  *pch, uchar  bMin, uchar  bMax, uchar  bDef)
{
  LoadCache(pch);
  uchar *pbVal = (uchar *) pch->pbBuff;

  if (!((*pbVal >= bMin) && (*pbVal <= bMax)))
  {
    *pbVal = bDef;
    SaveCache(pch);
  }
}


void    LoadCacheInt(cache const  *pch, uint  wMin, uint  wMax, uint  wDef)
{
  LoadCache(pch);
  uint *pwVal = (uint *) pch->pbBuff;

  if (!((*pwVal >= wMin) && (*pwVal <= wMax)))
  {
    *pwVal = wDef;
    SaveCache(pch);
  }
}
