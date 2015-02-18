/*------------------------------------------------------------------------------
IMPULSES.H


------------------------------------------------------------------------------*/

extern  volatile bool           fOnImpulse, fOnSecond;



void    EnableImpulses(void);
void    DisableImpulses(void);

void    Impulses_Timer1(void);

void    InitImpulses(void);
void    StartImpulses(void);
