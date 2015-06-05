/*------------------------------------------------------------------------------
OUT_COMMON,H


------------------------------------------------------------------------------*/

void    OutGetFloatCan(float  *mfl);
void    OutGetFloatOrDoubleCan_GlobalWork(double  *mdb, bool  fDouble);

void    OutSetFloatCan(float  *mfl, file const  *pfl);

void    OutFloatCanExt(float  *mpfl);
void    OutIntCanExt(uint  *mpw);
void    OutCharCanExt(uchar  *mpb);
void    OutBoolCanExt(bool  *mpf);
