/*------------------------------------------------------------------------------
PHONES,H


------------------------------------------------------------------------------*/

extern  cache const             chPhones;
extern  cache const             chMaxConnect;
extern  cache const             chCustomModem;

extern  bool                    boModemATDP;
extern  cache const             chModemATDP;



void    InitPhones(void);
void    ResetPhones(void);

bool    ValidPhone(line  *pph);
