/*------------------------------------------------------------------------------
PROFILE_CORE.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../flash/files.h"
#include "profile_core.h"



file const              flEnblCan = {ENBL_CAN, &mpboEnblCan, sizeof(mpboEnblCan)};

file const              flEnblCurrent = {ENBL_CURRENT, &boEnblCurrent, sizeof(bool)};
file const              flEnblProfile = {ENBL_PROFILE, &boEnblProfile, sizeof(bool)};

file const              flTimeoutCurrent = {TIMEOUT_CURRENT, &bTimeoutCurrent, sizeof(uchar)};
file const              flTimeoutProfile = {TIMEOUT_PROFILE, &bTimeoutProfile, sizeof(uchar)};



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
    mpboEnblCan[c] = true;

  SaveFile(&flEnblCan);

  boEnblCurrent = false;
  SaveFile(&flEnblCurrent);

  boEnblProfile = true;
  SaveFile(&flEnblProfile);

  bTimeoutCurrent = 2;
  SaveFile(&flTimeoutCurrent);

  bTimeoutProfile = 60;
  SaveFile(&flTimeoutProfile);
}
