/*------------------------------------------------------------------------------
OUT_COMMON,H


------------------------------------------------------------------------------*/

void    OutGetFloatOrDoubleCan(double  *mpdb, bool  fDouble);
void    OutGetFloatOrDoubleCan_GlobalWork(double  *mpdb, bool  fDouble);

void    OutSetFloatOrDoubleCan(double  *mpdb, cache const  *pch, bool  fDouble);

void    OutFloatOrDoubleCanExt(double  *mpdb, bool  fDouble);
void    OutIntCanExt(uint  *mpw);
void    OutCharCanExt(uchar  *mpb);
void    OutBoolCanExt(bool  *mpf);

uchar   PushStatusFloatOrDouble(status  bStatus, double  db, bool  fDouble);

uint    PushBoolArray(bool  *mpf, uchar  bCount);
void    OutBoolArray(bool  *mpf, uchar  bCount);

uint    PushIntBigArray(uint  *mpw, uchar  bCount);
