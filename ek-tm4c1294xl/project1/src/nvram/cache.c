/*------------------------------------------------------------------------------
CACHE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "23x1024.h"
#include "cache.h"



bool    SaveCache(cache const  *pch)
{
  return WriteNvramBuff(pch->wPage, pch->pbBuff, pch->wSize);
}


bool    LoadCache(cache const  *pch)
{
  return ReadNvramBuff(pch->wPage, pch->pbBuff, pch->wSize);
}
