/*------------------------------------------------------------------------------
PROFILE_CORE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../flash/files.h"



file const              flEnblCan = {FLS_ENBL_CAN, &mpboEnblCan, sizeof(mpboEnblCan)};



void    InitProfile(void)
{
  LoadFile(&flEnblCan);
}



void    ResetProfile(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
    mpboEnblCan[c] = TRUE;

  SaveFile(&flEnblCan);
}
