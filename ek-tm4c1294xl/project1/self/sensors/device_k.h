/*------------------------------------------------------------------------------
DEVICE_K.H


------------------------------------------------------------------------------*/

//#ifndef SKIP_K

void    PushAddress2Bcc(void);
void    PushLineBcc(uchar  ibLine);

void    PopRealK(void);

void    QueryCloseK(void);

void    QueryOpenK(void);
void    ReadOpenK(void);

void    QueryEnergySpecK(uchar  ibLine);
void    QueryEnergyAbsK(uchar  ibLine);
void    ReadEnergyK(uchar  ibLine);

void    QueryOptionK(void);
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
void    ReadHeaderK(void);

bool    ReadDataK(void);

void    ReadCurrentK(uchar  bMaxLine);

//#endif
