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
  Push(&mpcwOverflowHhr, sizeof(mpcwOverflowHhr));
  Output(sizeof(mpcwOverflowHhr));
}


void    OutGetErrorLink(void)
{
  InitPushCRC();
  Push(&mpcwErrorLink, sizeof(mpcwErrorLink));
  Output(sizeof(mpcwErrorLink));
}


void    OutGetEngFrac(void)
{
  InitPushCRC();
  Push(&mpreEngFrac, sizeof(mpreEngFrac));
  Output(sizeof(mpreEngFrac));
}


void    OutGetEngFracDigCan(void)
{
  InitPushCRC();
  Push(&mpreEngFracDigCan, sizeof(mpreEngFracDigCan));
  Output(sizeof(mpreEngFracDigCan));
}


void    OutResetEngFrac(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpreEngFrac, 0, sizeof(mpreEngFrac));
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetEngFracDigCan(void)
{
  if (enGlobal == GLB_REPROGRAM)
    memset(&mpreEngFracDigCan, 0, sizeof(mpreEngFracDigCan));
  else
    Result(bRES_NEEDREPROGRAM);
}
