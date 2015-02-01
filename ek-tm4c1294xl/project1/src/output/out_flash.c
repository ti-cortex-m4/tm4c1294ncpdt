/*------------------------------------------------------------------------------
OUT_FLASH.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_flash.h"
#include        "../memory/mem_settings.h"
#include        "../ports.h"
#include        "../flash/at45.h"
#include        "../hardware/memory.h"



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

    PushInt(GetCODEChecksum());
    PushInt(wPrivate);
    PushChar(bLogical);

    OutptrOutBuff(wPAGE_SIZE);
  } else if (bInBuff5*0x100 + bInBuff6 <= wFLA_END) {
    wPageIn = bInBuff5*0x100 + bInBuff6;

    if (SafePageRead() == 1)
      Outptr(&mpbPageIn, wPAGE_SIZE);
    else
      Result(bRES_BADFLASH);
  }
  else Result(bRES_BADADDRESS);
}
