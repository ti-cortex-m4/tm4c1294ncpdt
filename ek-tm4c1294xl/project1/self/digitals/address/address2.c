/*------------------------------------------------------------------------------
address2.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_phones.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "address2.h"



line                    mpphAsciiAddress[bCANALS];

cache const             chAddress2 = {ASCII_ADDRESS, &mpphAsciiAddress, sizeof(mpphAsciiAddress)};



void    InitAddress2(void)
{
  LoadCache(&chAddress2);
}



void    ResetAddress2(void)
{
  memset(&mpphAsciiAddress, 0, sizeof(mpphAsciiAddress));
  SaveCache(&chAddress2);
}

