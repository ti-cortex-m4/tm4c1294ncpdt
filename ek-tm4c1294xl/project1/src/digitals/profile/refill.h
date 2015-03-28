/*------------------------------------------------------------------------------
REFILL.H


------------------------------------------------------------------------------*/

extern  boolean                 boDsblRefill;


extern  file const              flDsblRefill;



void    InitRefill(void);
void    ResetRefill(void);

void    StartRefill(void);
void    MakeRefillWinter(time  *pti);
void    MakeRefill(time  *pti);
