/*------------------------------------------------------------------------------
ascii_address.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_phones.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "ascii_address.h"



line                    mpphAsciiAddress[bCANALS];
cache const             chAsciiAddress = {ASCII_ADDRESS, &mpphAsciiAddress, sizeof(mpphAsciiAddress)};

bool                    fHexAddresses;
cache const             chHexAddresses = {HEX_ADDRESSES, &fHexAddresses, sizeof(bool)};



void    InitAsciiAddress(void)
{
  LoadCache(&chAsciiAddress);

  LoadCacheBool(&chHexAddresses, false);
}



void    ResetAsciiAddress(void)
{
  memset(&mpphAsciiAddress, 0, sizeof(mpphAsciiAddress));
  SaveCache(&chAsciiAddress);

  SaveCacheBool(&chHexAddresses, false);
}

