/*------------------------------------------------------------------------------
OUT_ADDRESSES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../nvram/cache.h"



void    OutGetAddress(void)
{
  if (bInBuff6 < bCANALS)
  {
    InitPushCRC();
    PushLongBig(mpdwAddress1[bInBuff6]);
    PushLongBig(mpdwAddress2[bInBuff6]);
    Output(2*sizeof(ulong));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetAddress(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      InitPop(7);

      mpdwAddress1[bInBuff6] = PopLongBig();
      mpdwAddress2[bInBuff6] = PopLongBig();

      if (bInBuff6 == bCANALS - 1)
      {
        SaveCache(&chAddress1);
        SaveCache(&chAddress2);
      }

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutGetAddressesExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushLongBig(mpdwAddress1[c]);
      PushLongBig(mpdwAddress2[c]);
      wSize += sizeof(ulong)*2;
    }
  }

  OutptrOutBuff(wSize);
}
