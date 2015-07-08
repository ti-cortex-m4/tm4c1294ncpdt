/*------------------------------------------------------------------------------
PHONES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_phones.h"
#include "../flash/files.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "phones.h"



file const              flPhones = {PHONES, &mpphPhones, sizeof(mpphPhones)};
cache const             chMaxConnect = {MAX_CONNECT, &bMaxConnect, sizeof(uchar)};
cache const             chCustomModem = {CUSTOM_MODEM, &boCustomModem, sizeof(bool)};



void    InitPhones(void)
{
  LoadFile(&flPhones);

  LoadCacheChar(&chMaxConnect, 1, 180, 60);
  LoadCacheBoolean(&chCustomModem, false);
}



void    ResetPhones(void)
{
  memset(&mpphPhones, 0, sizeof(mpphPhones));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpphPhones[c].szNumber[0] = '0';
  }

  SaveFile(&flPhones);


  bMaxConnect = 60;
  SaveCache(&chMaxConnect);

  boCustomModem = false;
  SaveCache(&chCustomModem);
}



bool    IsValidPhone(phone  *pph)
{
  return true;
}

