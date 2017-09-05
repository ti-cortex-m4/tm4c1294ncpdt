/*------------------------------------------------------------------------------
PHONES2_OUT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_phones2.h"
#include "../../serial/ports.h"
#include "phones2_out.h"



void    OutPhones2(void) {
  InitPushCRC();

  uint  i;
  for (i=0; i<400; i++) PushChar(0);

  InitPushCRC();

  PushChar(boShowMessages);
  PushChar(UsePhones2());
  PushChar(bPortPhones2);

  PushFloat(reCurrPhones2);
  PushFloat(reMaxxPhones2);

  Push(&mpphPhones2, sizeof(mpphPhones2));

  PushChar(false);
  PushChar(bDelayPhone2);

  Push(&mpbAnswer1Phones2, sizeof(mpbAnswer1Phones2));
  Push(&mpbAnswer2Phones2, sizeof(mpbAnswer2Phones2));

  Push(&mpstPhones2, sizeof(mpstPhones2));

  Push(&mpbBuffPhones2, sizeof(mpbBuffPhones2));

  PushLongBig(cdwPhones20);
  PushLongBig(cdwPhones21);
  PushLongBig(cdwPhones22);
  PushLongBig(cdwPhones23);
  PushLongBig(cdwPhones24);
  PushLongBig(cdwPhones25);

  Output(400);
}
