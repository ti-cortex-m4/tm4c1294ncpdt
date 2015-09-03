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
  uint wPageIn = bInBuff5*0x100 + bInBuff6;

  if (wPageIn == 0xFFFF)
  {
    InitPushPtr();

    PushInt(cwFlashBusyErr);
    PushInt(cwFlashCompareWrn);
    PushInt(cwFlashEraseWrn);
    PushInt(cwFlashReadWrn);
    PushInt(cwFlashWriteWrn);
    PushInt(cwFlashCompareErr);
    PushInt(cwFlashEraseErr);
    PushInt(cwFlashReadErr);
    PushInt(cwFlashWriteErr);

    InitPush(63);

    PushInt(cwWrnResetWDT);

    PushInt(GetRomChecksum());
    PushInt(wPrivate);
    PushChar(bLogical);

    OutptrOutBuff(1056);
  }
  else if (wPageIn <= FLASH_END)
  {
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

  wSize += PushLong(cdwFlashErasePage);
  wSize += PushLong(cdwFlashReadPage);
  wSize += PushLong(cdwFlashWritePage);

  wSize += PushLong(cdwFlashReadByte);
  wSize += PushLong(cdwFlashWriteByte);

  wSize += PushInt(cwFlashBusyCnt);
  wSize += PushInt(cwFlashBusyErr);
  wSize += PushInt(cwFlashCompareWrn);
  wSize += PushInt(cwFlashCompareErr);
  wSize += PushInt(cwFlashEraseWrn);
  wSize += PushInt(cwFlashEraseErr);
  wSize += PushInt(cwFlashReadWrn);
  wSize += PushInt(cwFlashReadErr);
  wSize += PushInt(cwFlashWriteWrn);
  wSize += PushInt(cwFlashWriteErr);

  wSize += PushInt(cwFlashCompareErr1);
  wSize += PushInt(cwFlashCompareErr2);
  wSize += PushInt(cwFlashEraseErr1);
  wSize += PushInt(cwFlashEraseErr2);
  wSize += PushInt(cwFlashReadErr1);
  wSize += PushInt(cwFlashReadErr2);
  wSize += PushInt(cwFlashWriteErr1);
  wSize += PushInt(cwFlashWriteErr2);

  Output(wSize);
}


void    ResetFlashCounters(void)
{
  cdwFlashErasePage = 0;
  cdwFlashReadPage = 0;
  cdwFlashWritePage = 0;

  cdwFlashReadByte = 0;
  cdwFlashWriteByte = 0;

  cwFlashBusyCnt = 0;
  cwFlashBusyErr = 0;
  cwFlashCompareWrn = 0;
  cwFlashCompareErr = 0;
  cwFlashEraseWrn = 0;
  cwFlashEraseErr = 0;
  cwFlashReadWrn = 0;
  cwFlashReadErr = 0;
  cwFlashWriteWrn = 0;
  cwFlashWriteErr = 0;

  cwFlashCompareErr1 = 0;
  cwFlashCompareErr2 = 0;
  cwFlashEraseErr1 = 0;
  cwFlashEraseErr2 = 0;
  cwFlashReadErr1 = 0;
  cwFlashReadErr2 = 0;
  cwFlashWriteErr1 = 0;
  cwFlashWriteErr2 = 0;

  Result(bRES_OK);
}
