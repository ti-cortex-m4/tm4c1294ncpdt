/*------------------------------------------------------------------------------
FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_realtime.h"
#include "../kernel/crc-16.h"
#include "flash1.h"
#include "flash2.h"
#include "flash.h"



// количество повторов
#define FLASH_REPEATS   8



static bool PageErase(uint const  wPageOut)
{
  return PageErase2(wPageOut);
//  return (wPageOut < wPAGES) ? PageErase1(wPageOut) : PageErase2(wPageOut);
}


static bool PageRead(uint const  wPageIn)
{
  return PageRead2(wPageIn);
//  return (wPageIn < wPAGES) ? PageRead1(wPageIn) : PageRead2(wPageIn);
}


static bool PageWrite(uint const  wPageOut)
{
  return PageWrite2(wPageOut);
//  return (wPageOut < wPAGES) ? PageWrite1(wPageOut) : PageWrite2(wPageOut);
}



bool    SafePageErase(uint const  wPageOut)
{
  cdwPageErase++;

  uchar i;
  for (i=0; i<FLASH_REPEATS; i++)
  {
    if (PageErase(wPageOut) == true) break;
    cwWrnPageErase++;
  }

  if (i == FLASH_REPEATS)
  {
    cwErrPageErase++;
    return false;
  }
  else return true;
}



bool    SafePageRead(uint const  wPageIn)
{
  cdwPageRead++;

  uchar i;
  for (i=0; i<FLASH_REPEATS; i++)
  {
    if (PageRead(wPageIn) == true) break;
    cwWrnPageRead++;
  }

  if (i == FLASH_REPEATS)
  {
    cwErrPageRead++;
    return false;
  }
  else return true;
}



bool    SafePageWrite(uint const  wPageOut)
{
  cdwPageWrite++;

  mpbPageOut[wLEAF_BYTES+0] = 0;
  mpbPageOut[wLEAF_BYTES+1] = 0;

  mpbPageOut[wLEAF_BYTES+2] = wPageOut / 0x100;
  mpbPageOut[wLEAF_BYTES+3] = wPageOut % 0x100;

  memcpy(&mpbPageOut[wLEAF_BYTES+4], &tiCurr, sizeof(time));

  MakeCRC16(mpbPageOut, wPAGE_BYTES-2);

  mpbPageOut[wPAGE_BYTES-2] = bCRCHi;
  mpbPageOut[wPAGE_BYTES-1] = bCRCLo;

  uchar i;
  for (i=0; i<FLASH_REPEATS; i++)
  {
    if (PageWrite(wPageOut) == true) break;
    cwWrnPageWrite++;
  }

  if (i == FLASH_REPEATS)
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
