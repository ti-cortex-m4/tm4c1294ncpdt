/*------------------------------------------------------------------------------
CACHE2.H


------------------------------------------------------------------------------*/

void    SaveCacheBool(cache const  *pch, bool  fVal);
void    LoadCacheBool(cache const  *pch, bool  fDef);

void    LoadCacheChar(cache const  *pch, uchar  bMin, uchar  bMax, uchar  bDef);

void    LoadCacheInt(cache const  *pch, uint  wMin, uint  wMax, uint  wDef);
