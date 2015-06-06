/*------------------------------------------------------------------------------
OUT_COMMON,H


------------------------------------------------------------------------------*/

void    OutGetFloatOrDoubleCan(double  *mpdb, bool  fDouble);
void    OutGetFloatOrDoubleCan_GlobalWork(double  *mpdb, bool  fDouble);

void    OutSetFloatOrDoubleCan(double  *mpdb, file const  *pfl, bool  fDouble);

void    OutFloatOrDoubleCanExt(double  *mpdb, bool  fDouble);
void    OutIntCanExt(uint  *mpw);
void    OutCharCanExt(uchar  *mpb);
void    OutBoolCanExt(bool  *mpf);
