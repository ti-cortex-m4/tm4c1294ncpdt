/*------------------------------------------------------------------------------
PHONES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_phones.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "phones.h"



cache const             chPhones = {PHONES, &mpphPhones, sizeof(mpphPhones)};
cache const             chMaxConnect = {MAX_CONNECT, &bMaxConnect, sizeof(uchar)};
cache const             chCustomModem = {CUSTOM_MODEM, &boCustomModem, sizeof(bool)};



void    InitPhones(void)
{
  LoadCache(&chPhones);

  LoadCacheChar(&chMaxConnect, 1, 180, 60);
  LoadCacheBool(&chCustomModem, false);
}



void    ResetPhones(void)
{
  memset(&mpphPhones, 0, sizeof(mpphPhones));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpphPhones[c].szLine[0] = '0';
  }

  SaveCache(&chPhones);


  bMaxConnect = 60;
  SaveCache(&chMaxConnect);

  boCustomModem = false;
  SaveCache(&chCustomModem);
}



bool    ValidPhone(line  *pph)
{
  return true;
}

