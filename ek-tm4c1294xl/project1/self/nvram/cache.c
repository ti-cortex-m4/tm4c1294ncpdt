/*------------------------------------------------------------------------------
CACHE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "23x1024.h"
#include "cache.h"



bool    SaveCache(cache const  *pch)
{
  return WriteNvramBuff(pch->dwAddr, pch->pbBuff, pch->wSize);
}


bool    FreeCache(cache const  *pch)
{
  return FreeNvramBuff(pch->dwAddr, pch->wSize);
}


bool    LoadCache(cache const  *pch)
{
  return ReadNvramBuff(pch->dwAddr, pch->pbBuff, pch->wSize);
}



bool    SaveArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff)
{
  return WriteNvramBuff(dwAddr + (wSizeX + bNVRAM_FOOTER)*ibX, (uchar *)pBuff, wSizeX);
}


bool    FreeArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX)
{
  return FreeNvramBuff(dwAddr + (wSizeX + bNVRAM_FOOTER)*ibX, wSizeX);
}


bool    LoadArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff)
{
  return ReadNvramBuff(dwAddr + (wSizeX + bNVRAM_FOOTER)*ibX, (uchar *)pBuff, wSizeX);
}



bool    SaveArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff)
{
  return WriteNvramBuff(dwAddr + (wSizeX + bNVRAM_FOOTER)*ibX + wSizeY*ibY, (uchar *)pBuff, wSizeY);
}


bool    LoadArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff)
{
  return ReadNvramBuff(dwAddr + (wSizeX + bNVRAM_FOOTER)*ibX + wSizeY*ibY, (uchar *)pBuff, wSizeY);
}
