/*------------------------------------------------------------------------------
OUT_FLASH,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_program.h"
#include "../serial/ports.h"
#include "../flash/flash.h"
#include "../hardware/memory.h"
#include "out_flash.h"



void    OutFlashPage(void)
{
  uint w = bInBuff5*0x100 + bInBuff6;

  if (w == 0xFFFF)
  {
    InitPushPtr();

    PushInt(cwWrnBusy);
    PushInt(cwWrnCompare);
    PushInt(cwWrnPageErase);
    PushInt(cwWrnPageRead);
    PushInt(cwWrnPageWrite);
    PushInt(cwErrCompare);
    PushInt(cwErrPageErase);
    PushInt(cwErrPageRead);
    PushInt(cwErrPageWrite);

    InitPush(63);

    PushInt(cwWrnResetWDT);

    PushInt(GetRomChecksum());
    PushInt(wPrivate);
    PushChar(bLogical);

    OutptrOutBuff(1056);
  }
  else if (w <= FLASH_END)
  {
    wPageIn = w;

    if (SafePageRead(wPageIn) == true)
      Outptr(&mpbPageIn, wPAGE_BYTES);
    else
      Result(bRES_BADFLASH);
  }
  else Result(bRES_BADADDRESS);
}



void    OutFlashCounters(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushLong(cdwPageErase);
  wSize += PushLong(cdwPageRead);
  wSize += PushLong(cdwPageWrite);

  wSize += PushLong(cdwFlashReadBytes);
  wSize += PushLong(cdwFlashWriteBytes);

  wSize += PushInt(cwWrnBusy);
  wSize += PushInt(cwWrnCompare);
  wSize += PushInt(cwWrnPageErase);
  wSize += PushInt(cwWrnPageRead);
  wSize += PushInt(cwWrnPageWrite);
  wSize += PushInt(cwErrCompare);
  wSize += PushInt(cwErrPageErase);
  wSize += PushInt(cwErrPageRead);
  wSize += PushInt(cwErrPageWrite);

  Output(wSize);
}


void    ResetFlashCounters(void)
{
  cdwPageErase = 0;
  cdwPageRead = 0;
  cdwPageWrite = 0;

  cdwFlashReadBytes = 0;
  cdwFlashWriteBytes = 0;

  cwWrnBusy = 0;
  cwWrnCompare = 0;
  cwWrnPageErase = 0;
  cwWrnPageRead = 0;
  cwWrnPageWrite = 0;
  cwErrCompare = 0;
  cwErrPageErase = 0;
  cwErrPageRead = 0;
  cwErrPageWrite = 0;

  Result(bRES_OK);
}
