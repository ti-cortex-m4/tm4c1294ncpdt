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

    PushIntBig(cwFlashBusyErr);
    PushIntBig(cwFlashCompareWrn);
    PushIntBig(cwFlashEraseWrn);
    PushIntBig(cwFlashReadWrn);
    PushIntBig(cwFlashWriteWrn);
    PushIntBig(cwFlashCompareErr);
    PushIntBig(cwFlashEraseErr);
    PushIntBig(cwFlashReadErr);
    PushIntBig(cwFlashWriteErr);

    InitPush(63);

    PushIntBig(cwWrnResetWDT);

    PushIntBig(GetRomChecksum());
    PushIntBig(wPrivate);
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

  wSize += PushLongBig(cdwFlashErasePage);
  wSize += PushLongBig(cdwFlashReadPage);
  wSize += PushLongBig(cdwFlashWritePage);

  wSize += PushLongBig(cdwFlashReadByte);
  wSize += PushLongBig(cdwFlashWriteByte);

  wSize += PushIntBig(cwFlashBusyCnt);
  wSize += PushIntBig(cwFlashBusyErr);
  wSize += PushIntBig(cwFlashCompareWrn);
  wSize += PushIntBig(cwFlashCompareErr);
  wSize += PushIntBig(cwFlashEraseWrn);
  wSize += PushIntBig(cwFlashEraseErr);
  wSize += PushIntBig(cwFlashReadWrn);
  wSize += PushIntBig(cwFlashReadErr);
  wSize += PushIntBig(cwFlashWriteWrn);
  wSize += PushIntBig(cwFlashWriteErr);

  wSize += PushIntBig(cwFlashCompareErr1);
  wSize += PushIntBig(cwFlashCompareErr2);
  wSize += PushIntBig(cwFlashEraseErr1);
  wSize += PushIntBig(cwFlashEraseErr2);
  wSize += PushIntBig(cwFlashReadErr1);
  wSize += PushIntBig(cwFlashReadErr2);
  wSize += PushIntBig(cwFlashWriteErr1);
  wSize += PushIntBig(cwFlashWriteErr2);

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
