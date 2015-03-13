/*------------------------------------------------------------------------------
IMPULSES.H


------------------------------------------------------------------------------*/

#define NATIVE_IMPULSES



extern  volatile bool           fOnImpulse, fOnSecond;



void    EnableImpulses(void);
void    DisableImpulses(void);

void    Impulses_Timer0(void);
void    Impulses_1Hz(void);

void    InitImpulses(void);
void    StartImpulses(void);
