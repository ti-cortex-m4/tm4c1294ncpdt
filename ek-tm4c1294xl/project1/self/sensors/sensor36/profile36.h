/*------------------------------------------------------------------------------
profile36!H


------------------------------------------------------------------------------*/

// нижний порог коррекции времени, секунд
#define bMINORCORRECT_36 3



extern  uchar                   ibLine36, bMaxLine36;



void    InitHeader36(void);
void    QueryHeader36(void);
void    ReadHeader36(void);
void    ReadHeader36_SkipLine(uchar  ibLine);
void    MakeData36(uchar  ibHou);
bool    ReadData36(void);
