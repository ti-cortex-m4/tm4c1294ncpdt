/*------------------------------------------------------------------------------
PHONES,H


------------------------------------------------------------------------------*/

extern  cache const             chPhones;
extern  cache const             chMaxConnect;
extern  cache const             chCustomModem;



void    InitPhones(void);
void    ResetPhones(void);

bool    ValidPhone(line  *pph);
