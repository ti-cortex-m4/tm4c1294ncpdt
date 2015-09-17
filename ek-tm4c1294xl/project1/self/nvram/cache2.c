/*------------------------------------------------------------------------------
CACHE2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "cache.h"
#include "cache2.h"



void    SaveCacheBool(cache const  *pch, bool  f)
{
  bool *pf = (bool *) pch->pbBuff;
  *pf = f;

  SaveCache(pch);
}


void    LoadCacheBool(cache const  *pch, bool  fDef)
{
  LoadCache(pch);
  bool *pf = (bool *) pch->pbBuff;

  if (!((*pf == true) || (*pf == false)))
  {
    *pf = fDef;
    SaveCache(pch);
  }
}



void    SaveCacheChar(cache const  *pch, uchar  w)
{
  uchar *pb = (uchar *) pch->pbBuff;
  *pb = w;

  SaveCache(pch);
}


void    LoadCacheChar(cache const  *pch, uchar  bMin, uchar  bMax, uchar  bDef)
{
  LoadCache(pch);
  uchar *pb = (uchar *) pch->pbBuff;

  if (!((*pb >= bMin) && (*pb <= bMax)))
  {
    *pb = bDef;
    SaveCache(pch);
  }
}



void    SaveCacheInt(cache const  *pch, uint  w)
{
  uint *pw = (uint *) pch->pbBuff;
  *pw = w;

  SaveCache(pch);
}


void    LoadCacheInt(cache const  *pch, uint  wMin, uint  wMax, uint  wDef)
{
  LoadCache(pch);
  uint *pw = (uint *) pch->pbBuff;

  if (!((*pw >= wMin) && (*pw <= wMax)))
  {
    *pw = wDef;
    SaveCache(pch);
  }
}
