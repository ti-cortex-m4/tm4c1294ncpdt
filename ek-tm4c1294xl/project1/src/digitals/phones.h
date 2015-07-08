/*------------------------------------------------------------------------------
PHONES.H


------------------------------------------------------------------------------*/

extern  file const              flPhones;
extern  cache const             chMaxConnect;
extern  cache const             chCustomModem;



void    InitPhones(void);
void    ResetPhones(void);

bool    IsValidPhone(phone  *pph);
