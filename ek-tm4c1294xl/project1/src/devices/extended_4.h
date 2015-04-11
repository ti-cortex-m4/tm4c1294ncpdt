/*------------------------------------------------------------------------------
EXTENDED_4.H


------------------------------------------------------------------------------*/

#include        "../memory/mem_extended_4.h"



extern  file const              flExt4Flag;
extern  file const              flExt4Months;
extern  file const              flExt4EnblCan;



void    InitExtended4(void);
void    ResetExtended4(void);

void    NextDayExtended4(void);
void    NextMonExtended4(void);

void    MakeExtended4(void);

void    OutExtended40(void);
void    OutExtended401(void);
void    OutExtended41(void);
void    OutExtended42(void);
void    OutExtended43(void);

bool    ReadCntMonCanFCurr(uchar  ibMonth, uchar  ibCanal);
bool    ReadCntMonCanFBuff(uchar  ibMonth, uchar  ibCanal);
void    ShowCntMonCanF2(void);
void    ShowExtended4(uchar  ibCanal, uchar  ibMonth);
