/*------------------------------------------------------------------------------
OUT_PROFILE_LINK,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "out_profile_link.h"



void    OutGetProfileLinkWrn(void)
{
  InitPushCRC();

  uchar p;
  for (p=0; p<bPORTS; p++)
    PushIntBigArray(mpcwProfileLinkWrn[p], 48);

  Output(sizeof(mpcwProfileLinkWrn));
}


void    OutGetProfileLinkErr(void)
{
  InitPushCRC();

  uchar p;
  for (p=0; p<bPORTS; p++)
    PushIntBigArray(mpcwProfileLinkErr[p], 48);

  Output(sizeof(mpcwProfileLinkErr));
}


void    OutResetProfileLinkWrn(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpcwProfileLinkWrn, 0, sizeof(mpcwProfileLinkWrn));
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetProfileLinkErr(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpcwProfileLinkErr, 0, sizeof(mpcwProfileLinkErr));
  else
    Result(bRES_NEEDREPROGRAM);
}
