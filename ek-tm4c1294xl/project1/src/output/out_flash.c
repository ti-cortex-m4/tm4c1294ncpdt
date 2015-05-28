/*------------------------------------------------------------------------------
OUT_FLASH.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../flash/at45.h"
#include "../hardware/memory.h"



void    OutFlashPage(void) {
  if ((bInBuff5 == 0xFF) && (bInBuff6 == 0xFF)) {
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
  } else if (bInBuff5*0x100 + bInBuff6 <= END) {
    wPageIn = bInBuff5*0x100 + bInBuff6;

    if (SafePageRead() == true)
      Outptr(&mpbPageIn, wPAGE_SIZE);
    else
      Result(bRES_BADFLASH);
  }
  else Result(bRES_BADADDRESS);
}
