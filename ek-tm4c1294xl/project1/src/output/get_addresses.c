/*------------------------------------------------------------------------------
OUT_ADDRESSES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../flash/files.h"



void    OutGetAddressesExt(void)
{
    if (bInBuff6 < bCANALS)
    {
      InitPushCRC();
      Push(&mpdwAddress1[bInBuff6], sizeof(ulong));
      Push(&mpdwAddress2[bInBuff6], sizeof(ulong));
      Output(2*sizeof(ulong));
    }
    else Result(bRES_BADADDRESS);
}


void    OutSetAddressesExt(void)
{
    if (enGlobal == GLB_PROGRAM)
    {
      if (bInBuff6 < bCANALS)
      {
        InitPop(7);
        Pop(&mpdwAddress1[bInBuff6], sizeof(ulong));
        Pop(&mpdwAddress2[bInBuff6], sizeof(ulong));

        LongResult(bRES_OK);
      }
      else Result(bRES_BADADDRESS);
    }
    else Result(bRES_NEEDPROGRAM);
}
