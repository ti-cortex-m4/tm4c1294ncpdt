/*------------------------------------------------------------------------------
OUT_PROFILE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_profile.h"
#include "../../serial/ports.h"



void    OutGetOverflowHhr(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushInt(mpcwOverflowHhr[c]);
  }

  Output(sizeof(mpcwOverflowHhr));
}


void    OutGetErrorLink(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushInt(mpcwErrorLink[c]);
  }

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
  Push(&mpcwOutputZ, sizeof(mpcwOutputZ));
  Push(&mpcwOutputC, sizeof(mpcwOutputC));
  Push(&mpcwOutput0, sizeof(mpcwOutput0));
  Push(&mpcwOutput1, sizeof(mpcwOutput1));
  Push(&mpcwOutput2, sizeof(mpcwOutput2));
  Push(&mpcwOutput3, sizeof(mpcwOutput3));
  Output(6*64*2);

}
