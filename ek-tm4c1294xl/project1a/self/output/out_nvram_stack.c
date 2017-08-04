/*------------------------------------------------------------------------------
OUT_NVRAM_STACK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../include/nvram.h"
#include "out_nvram_stack.h"



void    OutNvramStack(void)
{
  InitPushCRC();

  uint i;
  for (i=0; i<4000; i++) PushChar(0);

  InitPushCRC();

  PUSH_VALUE(NVRAM_BEGIN)
  PUSH_VALUE(NVRAM_END)
  PUSH_VALUE(dwNVRAM_BYTES)

  PushChar(0x0D); PushChar(0x0A);

  PushLongAsString((ulong)100*(NVRAM_END-NVRAM_BEGIN)/(dwNVRAM_BYTES-NVRAM_BEGIN));
  PushString("%");

  PushChar(0x0D); PushChar(0x0A);
  PushChar(0x0D); PushChar(0x0A);

  #include "../generated/out_nvram.txt"

  Output(4000);
}
