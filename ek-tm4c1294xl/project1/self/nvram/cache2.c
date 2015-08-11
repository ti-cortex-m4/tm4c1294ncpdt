/*------------------------------------------------------------------------------
CACHE2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "cache.h"
#include "cache2.h"



void    LoadCacheBoolean(cache const  *pch, bool  boDef)
{
  LoadCache(pch);
  bool *pboVal = (bool *) pch->pbBuff;

  if (!((*pboVal == true) || (*pboVal == false)))
  {
    *pboVal = boDef;
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
