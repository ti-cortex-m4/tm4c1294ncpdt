/*------------------------------------------------------------------------------
CACHE2.H


------------------------------------------------------------------------------*/

void    SaveCacheBool(cache const  *pch, bool  f);
void    LoadCacheBool(cache const  *pch, bool  fDef);

void    SaveCacheChar(cache const  *pch, uchar  b);
void    LoadCacheChar(cache const  *pch, uchar  bMin, uchar  bMax, uchar  bDef);

void    SaveCacheInt(cache const  *pch, uint  w);
void    LoadCacheInt(cache const  *pch, uint  wMin, uint  wMax, uint  wDef);
