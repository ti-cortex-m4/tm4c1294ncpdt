/*------------------------------------------------------------------------------
PHONES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_phones.h"
#include        "../flash/files.h"



file const              flPhones = {FLS_PHONES, &mpphPhones, sizeof(phone)*bCANALS};
file const              flMaxConnect = {FLS_MAX_CONNECT, &bMaxConnect, sizeof(uchar)};



void    InitPhones(void)
{
  LoadFile(&flPhones);
  LoadFile(&flMaxConnect);

  boCustomModem = FALSE;
}



void    ResetPhones(void)
{
uchar   c;

  for (c=0; c<bCANALS; c++)
    strcpy((char *)mpphPhones[c].szNumber, "0");

  SaveFile(&flPhones);

  bMaxConnect = 60;
  SaveFile(&flMaxConnect);
}


#ifndef MODBUS
bool    TruePhone(void)
{
  return(1);
}
#endif
