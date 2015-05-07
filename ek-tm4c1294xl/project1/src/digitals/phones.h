/*------------------------------------------------------------------------------
PHONES.H


------------------------------------------------------------------------------*/

extern  file const              flPhones;
extern  file const              flMaxConnect;
extern  file const              flCustomModem;



void    InitPhones(void);
void    ResetPhones(void);

bool    TruePhone(phone  *pph);
