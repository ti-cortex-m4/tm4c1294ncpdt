/*------------------------------------------------------------------------------
OUT_FLASH_MAP.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"
#include        "../include/flash.h"



#define PUSH_ENUM(value) PushStringSkip(#value, 3); PushString("="); PushIntAsString(value); PushChar(0x0D); PushChar(0x0A);



void    OutFlashMap(void)
{
  InitPushCRC();

  uint i;
  for (i=0; i<2000; i++) PushChar(0);

  InitPushCRC();

  #include        "../include/out_flash.txt"

  Output(2000);
}
