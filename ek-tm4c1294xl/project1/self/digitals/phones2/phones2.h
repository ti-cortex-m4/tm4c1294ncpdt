/*------------------------------------------------------------------------------
PHONES2!H


------------------------------------------------------------------------------*/

#include "../../memory/mem_phones2.h"
#include "phones2_include.h"



extern float                  reCurrPhones2;
extern uchar                  mpbBuffPhones2[PHONE2_RECORD];
extern uchar                  mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];
extern uchar                  bDelayPhone2;
extern stamp2                 mpstPhones2[PHONE2_CODES];
extern ulong                  cdwPhones20, cdwPhones21, cdwPhones22, cdwPhones23, cdwPhones24, cdwPhones25;


extern cache const            chPortPhones2;
extern cache const            chPhones2;
extern cache const            chMaxxPhones2;



void    InitPhones2(void);
void    ResetPhones2(void);

bool    UsePhones2(void);



