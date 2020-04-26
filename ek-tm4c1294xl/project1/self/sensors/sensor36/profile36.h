/*------------------------------------------------------------------------------
DEVICE_U!H


------------------------------------------------------------------------------*/

#ifndef SKIP_U

// нижний порог коррекции времени, секунд
#define bMINORCORRECT_U 3



extern uchar                   ibLineU, bMaxLineU;



uchar   GetMaxLineU(uchar  ibCan);

void    QueryCloseU(void);
void    QueryOptionU(void);
void    QueryCorrectU(void);
void    QueryEngAbsU(uchar  ibLine);
void    QueryEngDayU(uchar  ibLine, time  ti);
void    QueryEngMonU(uchar  ibLine, time  ti);
void    QueryEngSpecU(uchar  ibLine);
void    ReadEngU(uchar  ibLine);
void    ReadEngU_SkipLine(uchar  ibLine);

void    InitHeaderU(void);
void    QueryHeaderU(void);
void    ReadHeaderU(void);
void    ReadHeaderU_SkipLine(uchar  ibLine);
void    MakeDataU(uchar  ibHou);
bool    ReadDataU(void);

void    ReadCurrentU(uchar  bMaxLine);

#endif

