/*------------------------------------------------------------------------------
REFILL.H


------------------------------------------------------------------------------*/

extern  boolean                 boDsblRefill;


extern  file const              flDsblRefill;



void    StartRefill(void);
void    MakeRefillWinter(time  *pti);
void    MakeRefill(time  *pti);
