/*------------------------------------------------------------------------------
OUT_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../nvram/23x1024.h"
#include "out_nvram.h"



void    OutNvram(void)
{
  ulong dwAddr = bInBuff6*0x10000 + bInBuff7*0x100 + bInBuff8;
  uint wSize = bInBuff9*0x100 + bInBuffA;

  if (dwAddr >= dwNVRAM_BYTES)
    Result(bRES_BADADDRESS);
  else if (5+wSize >= wOUTBUFF_SIZE-bMARGIN)
    Result(bRES_OUTOVERFLOW);
  else
  {
    InitPushCRC();

    if (PushNvramBuff(dwAddr, wSize))
      Output(wSize);
    else
      Result(bRES_BADFLASH);
  }
}
