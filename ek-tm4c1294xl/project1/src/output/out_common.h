/*------------------------------------------------------------------------------
OUT_COMMON,H


------------------------------------------------------------------------------*/

void    OutGetFloatCan(float  *mfl);
void    OutGetFloatOrDoubleCan_GlobalWork(double  *mdb, bool  fDouble);

void    OutSetFloatCan(float  *mfl, file const  *pfl);

void    OutFloatCanMap(real  *mpe);
void    OutIntCanMap(uint  *mpw);
void    OutCharCanMap(uchar  *mpb);
void    OutBoolCanMap(boolean  *mpf);
