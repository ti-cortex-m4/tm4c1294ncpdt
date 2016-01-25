/*------------------------------------------------------------------------------
DEVICE31.H


------------------------------------------------------------------------------*/

#define MAX_LINE_N31    6



uchar   GetVersion31(void);
bool    ExtVersion31(void);

float   PopFloatN31(void);
double  PopDoubleN31(void);

void    QueryOpenN31(void);
bool    ReadOpenN31(void);

void    QueryTimeN31(void);
time    ReadTimeN31(void);
time    ReadPackTimeN31(void);
void    QueryControlN31(time  ti);

void    QueryTransN31(void);

void    QueryEngAbsN31(void);
void    ReadEngN31();

void    ReadCurrentN31(void);
