/*------------------------------------------------------------------------------
OUT_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_nvram.h"
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
    PushChar(ReadNvramStatus());

    if (PushNvramBuff(dwAddr, wSize))
      Output(1+wSize);
    else
      Result(bRES_BADFLASH);
  }
}



void    OutNvramCounters(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushLong(cdwNvramRead);
  wSize += PushLong(cdwNvramWrite);
  wSize += PushLong(cdwNvramFree);

  wSize += PushInt(cwWrnNvramRead);
  wSize += PushInt(cwErrNvramRead);
  wSize += PushInt(cwWrnNvramWrite);
  wSize += PushInt(cwErrNvramWrite);
  wSize += PushInt(cwWrnNvramFree);
  wSize += PushInt(cwErrNvramFree);
  wSize += PushInt(cwWrnNvramCompare);
  wSize += PushInt(cwErrNvramCompare);

  Output(wSize);
}
