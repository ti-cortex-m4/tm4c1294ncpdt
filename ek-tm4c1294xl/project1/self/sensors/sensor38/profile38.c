/*------------------------------------------------------------------------------
profile38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "profile38.h"



void    QueryProfile38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);
  PushChar(0x01 + ibLine); // A+, A-, R+, R-

  PushChar(0x02);
  PushChar(0x00);

  Query38(100+17, 16);
}
