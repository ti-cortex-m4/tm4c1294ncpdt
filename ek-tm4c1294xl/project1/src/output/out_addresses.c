/*------------------------------------------------------------------------------
OUT_ADDRESSES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../flash/files.h"



void    OutGetAddresses(void)
{
  if (bInBuff6 < bCANALS)
  {
    InitPushCRC();
    PushLong(mpdwAddress1[bInBuff6]);
    PushLong(mpdwAddress2[bInBuff6]);
    Output(2*sizeof(ulong));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetAddresses(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      InitPop(7);

      mpdwAddress1[bInBuff6] = PopLong();
      mpdwAddress2[bInBuff6] = PopLong();

      if (bInBuff6 == bCANALS - 1)
      {
        SaveFile(&flAddress1);
        SaveFile(&flAddress2);
      }

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
