/*------------------------------------------------------------------------------
CACHE.H


------------------------------------------------------------------------------*/

#include "../include/nvram.h"



bool    SaveCache(cache const  *pfl);
bool    LoadCache(cache const  *pfl);

bool    SaveArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff);
bool    FreeArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX);
bool    LoadArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff);

bool    SaveArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff);
bool    LoadArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff);
