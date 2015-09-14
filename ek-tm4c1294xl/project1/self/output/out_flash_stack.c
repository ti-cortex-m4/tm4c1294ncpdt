/*------------------------------------------------------------------------------
OUT_FLASH_STACK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../include/flash.h"
#include "out_flash_stack.h"



void    OutFlashStack(void)
{
  InitPushCRC();

  uint i;
  for (i=0; i<3000; i++) PushChar(0);

  InitPushCRC();

  PUSH_VALUE(FLASH_BEGIN)
  PUSH_VALUE(LOCAL_END)
  PUSH_VALUE(LOCAL_BEGIN)
  PUSH_VALUE(FLASH_END)
  PUSH_VALUE(wPAGES)
  PUSH_VALUE(wPAGES_TOTAL)
  PUSH_VALUE(wPAGE_BYTES)
  PUSH_VALUE(wLEAF_BYTES)

  PushChar(0x0D); PushChar(0x0A);

  PushLongAsString((ulong)100*(LOCAL_END-FLASH_BEGIN)/wPAGES);
  PushString("%");

  PushChar(0x0D); PushChar(0x0A);

  PushLongAsString((ulong)100*(FLASH_END-LOCAL_BEGIN)/wPAGES);
  PushString("%");

  PushChar(0x0D); PushChar(0x0A);
  PushChar(0x0D); PushChar(0x0A);

  PUSH_VALUE(UINT_CAN_PAGES)
  PUSH_VALUE(IMPHOUCAN_PAGES)
  PUSH_VALUE(IMP_CAN_PAGES)
  PUSH_VALUE(MAXPOW_GRP_PAGES)
  PUSH_VALUE(FLOAT_CAN_PAGES)
  PUSH_VALUE(DOUBLE_CAN_PAGES)
  PUSH_VALUE(PARAMS_PAGES)
  PUSH_VALUE(VALUE4_CAN_PAGES)
  PUSH_VALUE(VALUE4T_CAN_PAGES)
  PUSH_VALUE(VALUE5_CAN_PAGES)
  PUSH_VALUE(VALUE6_CAN_PAGES)
  PUSH_VALUE(VALUE7_CAN_PAGES)
  PUSH_VALUE(DIAGRAM_CAN_PAGES)
  PUSH_VALUE(DIAGRAM_PAGES)

  PushChar(0x0D); PushChar(0x0A);

  PUSH_VALUE(bRECORD_BLOCK)
  PUSH_VALUE(bRECORD_PAGES)
  PUSH_VALUE(wRECORD2_PAGES)

  PushChar(0x0D); PushChar(0x0A);

  #include "../include/out_flash.txt"

  Output(3000);
}
