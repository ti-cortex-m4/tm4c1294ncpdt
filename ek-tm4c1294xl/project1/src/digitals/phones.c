/*------------------------------------------------------------------------------
PHONES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_phones.h"
#include        "../flash/files.h"



file const              flPhones = {FLS_PHONES, &mpphPhones, sizeof(mpphPhones)};
file const              flMaxConnect = {FLS_MAX_CONNECT, &bMaxConnect, sizeof(uchar)};
file const              flCustomModem = {FLS_CUSTOM_MODEM, &boCustomModem, sizeof(bool)};



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


#ifndef MODBUS
bool    TruePhone(void)
{
  return(1);
}
#endif
