/*------------------------------------------------------------------------------
FLASH.C

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../include/flash.h"
#include "flash_control.h"
#include "../kernel/crc-16.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "flash1.h"
#include "../time/delay.h"
#include "flash_define1.h"



uint    GetFlashStatus(void)
{
uint    i;

  i = 0;

  if (cwErrCompare   != 0) i |= 0x0001;
  if (cwErrPageErase != 0) i |= 0x0002;
  if (cwErrPageRead  != 0) i |= 0x0004;
  if (cwErrPageWrite != 0) i |= 0x0008;

  return(i);
}


bool GetFlashChecksum(void)
{
  MakeCRC16(mpbPageIn, wPAGE_BYTES);

  if ((bCRCHi != 0x00) && (bCRCLo != 0x00))
  {
    if ((bCRCHi != 0x0F) && (bCRCLo != 0x74))
      return false;
  }

  return true;
}


/*
void    TODO OutFlashReadStatus(void) { + add (++i > wREAD_STATUS) + add cwWrnBusy etc
  InitPushCRC();

  ReadStatus();
  PushChar(bStatusFlash);

  PushChar(ReadStatus());

  Output(sizeof(char)+sizeof(char));
}
*/
