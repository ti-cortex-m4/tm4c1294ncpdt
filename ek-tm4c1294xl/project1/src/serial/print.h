/*------------------------------------------------------------------------------
PRINT,H


------------------------------------------------------------------------------*/

//#define ENABLE_PRINT



void    PrintStart(void);
void    PrintStop(void);

void    PrintString(const char  *psz);
void    PrintChar(uchar  b);
void    PrintInt(uint  w);
void    PrintLong(ulong  dw);
void    PrintTime(time  ti);
