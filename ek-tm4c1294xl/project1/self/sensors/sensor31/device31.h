/*------------------------------------------------------------------------------
DEVICE31.H


------------------------------------------------------------------------------*/

#define MAX_LINE_N31    6



uchar   GetVersion31(void);
bool    ExtVersion31(void);

float   PopFloat31(void);
double  PopDouble31(void);

void    QueryOpen31(void);
bool    ReadOpen31(void);

void    QueryTime31(void);
time    ReadTime31(void);
time    ReadPackTime31(void);
void    QueryControl31(time  ti);

void    QueryTrans31(void);

void    QueryEngAbs31(void);
void    ReadEng31();

void    ReadCurrent31(void);
