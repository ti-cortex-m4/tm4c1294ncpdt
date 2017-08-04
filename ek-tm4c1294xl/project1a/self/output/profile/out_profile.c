/*------------------------------------------------------------------------------
OUT_PROFILE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../digitals/profile/profile_frac.h"
#include "out_profile.h"



void    OutGetFailure2(void)
{
  InitPushCRC();
  PushIntBigArray(mpcwFailure2, bCANALS);
  Output(sizeof(mpcwFailure2));
}


void    OutGetOverflowHhr(void)
{
  InitPushCRC();
  PushIntBigArray(mpcwOverflowHhr, bCANALS);
  Output(sizeof(mpcwOverflowHhr));
}


void    OutGetErrorLink(void)
{
  InitPushCRC();
  PushIntBigArray(mpcwErrorLink, bCANALS);
  Output(sizeof(mpcwErrorLink));
}


void    OutGetEngFrac(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushDouble(mpdbEngFrac[c]);
  }

  Output(sizeof(mpdbEngFrac));
}


void    OutGetEngFracDigCan(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    uchar i;
    for (i=0; i<6; i++)
    {
      PushDouble(mpdbEngFracDigCan[c][i]);
    }
  }

  Output(sizeof(mpdbEngFracDigCan));
}


void    OutResetEngFrac(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpdbEngFrac, 0, sizeof(mpdbEngFrac));
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetEngFracDigCan(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    memset(&mpdbEngFracDigCan, 0, sizeof(mpdbEngFracDigCan));
    SaveProfileFrac6_All();
  }
  else
    Result(bRES_NEEDREPROGRAM);
}



void    OutCorrectLimit(void)
{
  InitPushCRC();
  Push(&mpbCorrectLimit, sizeof(mpbCorrectLimit));
  Output(sizeof(mpbCorrectLimit));
}


void    OutLinkErrors(void)
{
  InitPushCRC();
  PushIntBigArray(mpcwOutputZ, bCANALS);
  PushIntBigArray(mpcwOutputC, bCANALS);
  PushIntBigArray(mpcwOutput0, bCANALS);
  PushIntBigArray(mpcwOutput1, bCANALS);
  PushIntBigArray(mpcwOutput2, bCANALS);
  PushIntBigArray(mpcwOutput3, bCANALS);
  Output(6*bCANALS*2);

}
