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

  wSize += PushLong(cdwNvramReadBuff);
  wSize += PushLong(cdwNvramWriteBuff);
  wSize += PushLong(cdwNvramFreeBuff);

  wSize += PushLong(cdwNvramReadByte);
  wSize += PushLong(cdwNvramWriteByte);

  wSize += PushInt(cwNvramReadWrn);
  wSize += PushInt(cwNvramReadErr);
  wSize += PushInt(cwNvramWriteWrn);
  wSize += PushInt(cwNvramWriteErr);
  wSize += PushInt(cwNvramFreeWrn);
  wSize += PushInt(cwNvramFreeErr);
  wSize += PushInt(cwNvramCompareWrn);
  wSize += PushInt(cwNvramCompareErr);

  Output(wSize);
}


void    ResetNvramCounters(void)
{
  cdwNvramReadBuff = 0;
  cdwNvramWriteBuff = 0;
  cdwNvramFreeBuff = 0;

  cdwNvramReadByte = 0;
  cdwNvramWriteByte = 0;

  cwNvramReadWrn = 0;
  cwNvramReadErr = 0;
  cwNvramWriteWrn = 0;
  cwNvramWriteErr = 0;
  cwNvramFreeWrn = 0;
  cwNvramFreeErr = 0;
  cwNvramCompareWrn = 0;
  cwNvramCompareErr = 0;

  Result(bRES_OK);
}
