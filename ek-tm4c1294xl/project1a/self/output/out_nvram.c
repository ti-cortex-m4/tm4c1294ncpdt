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

  wSize += PushLongBig(cdwNvramReadBuff);
  wSize += PushLongBig(cdwNvramWriteBuff);
  wSize += PushLongBig(cdwNvramFreeBuff);

  wSize += PushLongBig(cdwNvramReadByte);
  wSize += PushLongBig(cdwNvramWriteByte);

  wSize += PushIntBig(cwNvramReadWrn);
  wSize += PushIntBig(cwNvramReadErr);
  wSize += PushIntBig(cwNvramWriteWrn);
  wSize += PushIntBig(cwNvramWriteErr);
  wSize += PushIntBig(cwNvramFreeWrn);
  wSize += PushIntBig(cwNvramFreeErr);
  wSize += PushIntBig(cwNvramCompareWrn);
  wSize += PushIntBig(cwNvramCompareErr);

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
