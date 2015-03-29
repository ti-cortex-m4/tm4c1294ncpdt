/*------------------------------------------------------------------------------
PROFILE_CORE.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../flash/files.h"
#include        "profile_core.h"



file const              flEnblCan = {FLS_ENBL_CAN, &mpboEnblCan, sizeof(mpboEnblCan)};

file const              flEnblCurrent = {FLS_ENBL_CURRENT, &boEnblCurrent, sizeof(boolean)};
file const              flEnblProfile = {FLS_ENBL_PROFILE, &boEnblProfile, sizeof(boolean)};

file const              flTimeoutCurrent = {FLS_TIMEOUT_CURRENT, &bTimeoutCurrent, sizeof(uchar)};
file const              flTimeoutProfile = {FLS_TIMEOUT_PROFILE, &bTimeoutProfile, sizeof(uchar)};



void    InitProfile(void)
{
  LoadFile(&flEnblCan);

  LoadFile(&flEnblCurrent);
  LoadFile(&flEnblProfile);

  LoadFile(&flTimeoutCurrent);
  LoadFile(&flTimeoutProfile);
}



void    ResetProfile(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
    mpboEnblCan[c] = TRUE;

  SaveFile(&flEnblCan);

  boEnblCurrent = TRUE;
  SaveFile(&flEnblCurrent);

  boEnblProfile = TRUE;
  SaveFile(&flEnblProfile);

  bTimeoutCurrent = 2;
  SaveFile(&flTimeoutCurrent);

  bTimeoutProfile = 60;
  SaveFile(&flTimeoutProfile);
}
