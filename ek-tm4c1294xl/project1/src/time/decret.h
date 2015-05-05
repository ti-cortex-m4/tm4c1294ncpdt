/*------------------------------------------------------------------------------
DECRET.H


------------------------------------------------------------------------------*/

extern  file const              flDecret;
extern  file const              flSummer;
extern  file const              flWinter;



void    MakeDecret(void);

void    InitDecret(void);
void    ResetDecret(void);

bool    IsWinter(time  ti);
uchar   GetSeasonMD(uchar  bMonth, uchar  bDay);
