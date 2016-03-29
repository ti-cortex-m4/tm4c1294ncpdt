/*------------------------------------------------------------------------------
DEVICE33.H


------------------------------------------------------------------------------*/

#define MAX_LINE_N33    1



//ulong   PopChar3Big33(void);

void    QueryOpen33(void);
bool    ReadOpen33(void);
//uchar   GetVersion33(void);
//bool    OldVersion33(void);

void    QueryTime33(void);
time    ReadTime33(void);
//time    ReadPackTime33(void);
//void    QueryControl33(time  ti);

void    QueryEngAbs33(uchar  ibTrf);

bool    Checksum33(uchar  bSize);
