/*------------------------------------------------------------------------------
OUT_FLASH.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_flash.h"
#include        "../ports.h"
#include        "../flash/at45.h"



void    OutFlashPage(void) {
  if (bInBuff5*0x100 + bInBuff6 <= wFLA_END) {
    wPageIn = bInBuff5*0x100 + bInBuff6;

    if (SafePageRead() == 1)
      Outptr(&mpbPageIn, wPAGE_SIZE);
    else
      Result(bRES_BADFLASH);
  }
  else Result(bRES_BADADDRESS);
}
