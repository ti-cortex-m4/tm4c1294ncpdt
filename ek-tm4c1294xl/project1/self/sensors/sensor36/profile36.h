/*------------------------------------------------------------------------------
profile36!H


------------------------------------------------------------------------------*/

// нижний порог коррекции времени, секунд
#define bMINORCORRECT_36 3



extern  uint                    wProfile36;
extern  uint                    cwShutdown36;

extern  time                    tiValue36;
extern  ulong                   dwValue36;

extern  uchar                   ibLine36, bMaxLine36;



bool    HasPassword36(void);
void    QueryPassword36(void);

void    QueryCorrect36(void);
void    QueryControl36(time  ti);

void    QueryTimeProfile36(void);
void    QueryDateProfile36(void);

void    InitHeader36(void);
void    QueryHeader36(void);
void    ReadHeader36(void);
void    ReadHeader36_SkipLine(uchar  ibLine);
void    MakeData36(uchar  ibHou);
bool    ReadData36(void);
