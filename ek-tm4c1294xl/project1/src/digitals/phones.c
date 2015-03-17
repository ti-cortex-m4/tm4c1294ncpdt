/*------------------------------------------------------------------------------
PHONES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../flash/files.h"



file const              flPhones = {FLS_PHONES, &mpphPhones, sizeof(phone)*bCANALS};
file const              flMaxConnect = {FLS_MAX_CONNECT, &bMaxConnect, sizeof(uchar)};



void    InitPhones(void)
{
  LoadFile(&flPhones);
  LoadFile(&flMaxConnect);
}



void    ResetPhones(void)
{
uchar   i;

  for (i=0; i<bCANALS; i++)
    strcpy(&mpphPhones[i].szNumber, "0");

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
