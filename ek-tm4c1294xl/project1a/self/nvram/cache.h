/*------------------------------------------------------------------------------
CACHE!H


------------------------------------------------------------------------------*/

#include "../include/nvram.h"



bool    SaveCache(cache const  *pch);
bool    FreeCache(cache const  *pch);
bool    LoadCache(cache const  *pch);

bool    SaveArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff);
bool    FreeArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX);
bool    LoadArrayX(ulong  dwAddr, uint  wSizeX, uchar  ibX, void  *pBuff);

bool    SaveArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff);
bool    LoadArrayXY(ulong  dwAddr, uint  wSizeX, uchar  ibX, uint  wSizeY, uchar  ibY, void  *pBuff);
