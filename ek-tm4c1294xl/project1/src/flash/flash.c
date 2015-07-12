/*------------------------------------------------------------------------------
FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_realtime.h"
#include "../kernel/crc-16.h"
#include "flash1.h"
#include "flash.h"



bool    SafePageErase(void)
{
  cdwPageErase++;

  uchar i;
  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageErase1() == 0)
    {
      cwWrnPageErase++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageErase++;
    return false;
  }
  else return true;
}



bool    SafePageRead(void)
{
  cdwPageRead++;

  uchar i;
  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageRead1() == 0)
    {
      cwWrnPageRead++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageRead++;
    return false;
  }
  else return true;
}



bool    SafePageWrite(void)
{
  mpbPageOut[wLEAF_BYTES+0] = 0;
  mpbPageOut[wLEAF_BYTES+1] = 0;

  mpbPageOut[wLEAF_BYTES+2] = wPageOut / 0x100;
  mpbPageOut[wLEAF_BYTES+3] = wPageOut % 0x100;

  memcpy(&mpbPageOut[wLEAF_BYTES+4], &tiCurr, sizeof(time));

  MakeCRC16(mpbPageOut, wPAGE_BYTES-2);

  mpbPageOut[wPAGE_BYTES-2] = bCRCHi;
  mpbPageOut[wPAGE_BYTES-1] = bCRCLo;

  cdwPageWrite++;

  uchar i;
  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageWrite1() == 0)
    {
      cwWrnPageWrite++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageWrite++;
    return false;
  }
  else return true;
}



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
