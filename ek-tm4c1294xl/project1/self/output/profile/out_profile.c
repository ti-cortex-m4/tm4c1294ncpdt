/*------------------------------------------------------------------------------
OUT_PROFILE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "out_profile.h"



void    OutGetFailure2(void)
{
  InitPushCRC();
  PushIntArray(mpcwFailure2, bCANALS);
  Output(sizeof(mpcwFailure2));
}


void    OutGetOverflowHhr(void)
{
  InitPushCRC();
  PushIntArray(mpcwOverflowHhr, bCANALS);
  Output(sizeof(mpcwOverflowHhr));
}


void    OutGetErrorLink(void)
{
  InitPushCRC();
  PushIntArray(mpcwErrorLink, bCANALS);
  Output(sizeof(mpcwErrorLink));
}


void    OutGetEngFrac(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushFloat(mpflEngFrac[c]);
  }

  Output(sizeof(mpflEngFrac));
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
      PushFloat(mpflEngFracDigCan[c][i]);
    }
  }

  Output(sizeof(mpflEngFracDigCan));
}


void    OutResetEngFrac(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpflEngFrac, 0, sizeof(mpflEngFrac));
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetEngFracDigCan(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpflEngFracDigCan, 0, sizeof(mpflEngFracDigCan));
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
  PushIntArray(mpcwOutputZ, bCANALS);
  PushIntArray(mpcwOutputC, bCANALS);
  PushIntArray(mpcwOutput0, bCANALS);
  PushIntArray(mpcwOutput1, bCANALS);
  PushIntArray(mpcwOutput2, bCANALS);
  PushIntArray(mpcwOutput3, bCANALS);
  Output(6*bCANALS*2);

}
