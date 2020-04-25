/*------------------------------------------------------------------------------
DEVICE_K.H


------------------------------------------------------------------------------*/

#ifndef SKIP_K

// нижний порог коррекции времени, секунд
#define bMINORCORRECT_K 3



uchar   PushAddress1Bcc(void);
uchar   PushAddress2Bcc(void);
void    PushLineBcc(uchar  ibLine);

double  PopDoubleK(void);

void    QueryCloseK(void);

void    QueryOpenK(void);
void    ReadOpenK(void);

void    QueryEnergySpecK(uchar  ibLine);
void    QueryEnergyAbsK(uchar  ibLine);
void    ReadEnergyK(uchar  ibLine);

void    QueryOptionK(void);
bool    HasPasswordK(void);
void    QueryPasswordK(void);

void    QueryTimeK(void);
void    QueryTimeSpecK(void);
time    ReadTimeK(void);

void    QueryDateK(void);
void    QueryDateSpecK(void);
time    ReadDateK(time  ti);

void    QueryCorrectK(void);
void    QueryControlK(void);

void    QueryHeaderK(void);
void    ReadHeaderK(uchar  ibLine);

bool    ReadDataK(void);

void    ReadCurrentK(uchar  bMaxLine);

#endif
