/*------------------------------------------------------------------------------
DEVICE32.H


------------------------------------------------------------------------------*/

#define MAX_LINE_N32    1



ulong   PopChar3Big32(void);

void    QueryOpen32(void);
bool    ReadOpen32(void);
uchar   GetVersion32(void);
bool    OldVersion32(void);

void    QueryTime32(void);
time    ReadTime32(void);
time    ReadPackTime32(void);
void    QueryControl32(time  ti);

void    QueryEngAbs32(uchar  ibTrf);

bool    Checksum32(uchar  bSize);
