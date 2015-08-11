/*------------------------------------------------------------------------------
REFILL.H


------------------------------------------------------------------------------*/

extern  bool                    boDsblRefill;

extern  uint                    iwBmin, iwBmax;

extern  cache const             chDsblRefill;



void    InitRefill(void);
void    ResetRefill(void);

void    StartRefill(void);
void    MakeRefillWinter(time  ti);
void    MakeRefill(time  ti);
