/*------------------------------------------------------------------------------
REFILL.H


------------------------------------------------------------------------------*/

extern  bool                    boDsblRefill;


extern  file const              flDsblRefill;



void    InitRefill(void);
void    ResetRefill(void);

void    StartRefill(void);
void    MakeRefillWinter(time  ti);
void    MakeRefill(time  ti);
