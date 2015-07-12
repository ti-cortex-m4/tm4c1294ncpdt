/*------------------------------------------------------------------------------
FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../kernel/crc-16.h"
#include "flash.h"



uint    GetFlashStatus(void)
{
  uint i = 0;

  if (cwErrCompare   != 0) i |= 0x0001;
  if (cwErrPageErase != 0) i |= 0x0002;
  if (cwErrPageRead  != 0) i |= 0x0004;
  if (cwErrPageWrite != 0) i |= 0x0008;

  return(i);
}


bool    GetFlashChecksum(void)
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
