/*------------------------------------------------------------------------------
OUT_FLASH,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../flash/at45.h"
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

    InitPush(65);

    PushInt(GetRomChecksum());
    PushInt(wPrivate);
    PushChar(bLogical);

    OutptrOutBuff(1056);
  }
  else if (w <= FLASH_END)
  {
    wPageIn = w;

    if (SafePageRead() == true)
      Outptr(&mpbPageIn, wPAGE_BYTES);
    else
      Result(bRES_BADFLASH);
  }
  else Result(bRES_BADADDRESS);
}
