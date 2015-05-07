/*------------------------------------------------------------------------------
PHONES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_phones.h"
#include "../flash/files.h"



file const              flPhones = {PHONES, &mpphPhones, sizeof(mpphPhones)};
file const              flMaxConnect = {MAX_CONNECT, &bMaxConnect, sizeof(uchar)};
file const              flCustomModem = {CUSTOM_MODEM, &boCustomModem, sizeof(bool)};



void    InitPhones(void)
{
  LoadFile(&flPhones);

  LoadFile(&flMaxConnect);
  if ((bMaxConnect == 0) || (bMaxConnect > 180))
  {
  	bMaxConnect = 60;
    SaveFile(&flMaxConnect);
  }

  LoadFile(&flCustomModem);
}



void    ResetPhones(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
    strcpy((char *)mpphPhones[c].szNumber, "0");

  SaveFile(&flPhones);

  bMaxConnect = 60;
  SaveFile(&flMaxConnect);

  boCustomModem = FALSE;
  SaveFile(&flCustomModem);
}



bool    TruePhone(phone  *pph)
{
  return true;
}

