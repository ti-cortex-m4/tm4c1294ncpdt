/*------------------------------------------------------------------------------
DECRET.H


------------------------------------------------------------------------------*/

extern  cache const             chDecret;
extern  cache const             chSummer;
extern  cache const             chWinter;



void    MakeDecret(void);

void    InitDecret(void);
void    ResetDecret(void);

bool    IsWinter(time  ti);
uchar   GetSeasonMD(uchar  bMonth, uchar  bDay);

uchar   Season(time  ti);
uchar   SeasonCurr(void);
