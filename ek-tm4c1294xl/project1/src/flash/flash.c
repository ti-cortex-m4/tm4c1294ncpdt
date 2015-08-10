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
  ASSERT(wPageOut < wPAGES_TOTAL);
//  return PageErase1(wPageOut);
  return (wPageOut < wPAGES) ? PageErase1(wPageOut) : PageErase2(wPageOut-wPAGES);
}


static bool PageRead(uint const  wPageIn)
{
  ASSERT(wPageIn < wPAGES_TOTAL);
//  return PageRead1(wPageIn);
  return (wPageIn < wPAGES) ? PageRead1(wPageIn) : PageRead2(wPageIn-wPAGES);
}


static bool PageWrite(uint const  wPageOut)
{
  ASSERT(wPageOut < wPAGES_TOTAL);
//  return PageWrite1(wPageOut);
  return (wPageOut < wPAGES) ? PageWrite1(wPageOut) : PageWrite2(wPageOut-wPAGES);
}



bool    SafePageErase(uint const  wPageOut)
{
  cdwFlashErasePage++;

  uchar i;
  for (i=0; i<FLASH_REPEATS; i++)
  {
    if (PageErase(wPageOut) == true) break;
    cwFlashEraseWrn++;
  }

  if (i == FLASH_REPEATS)
  {
    cwFlashEraseErr++;
    return false;
  }
  else return true;
}



bool    SafePageRead(uint const  wPageIn)
{
  cdwFlashReadPage++;

  uchar i;
  for (i=0; i<FLASH_REPEATS; i++)
  {
    if (PageRead(wPageIn) == true) break;
    cwFlashReadWrn++;
  }

  if (i == FLASH_REPEATS)
  {
    cwFlashReadErr++;
    return false;
  }
  else return true;
}



bool    SafePageWrite(uint const  wPageOut)
{
  cdwFlashWritePage++;

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
    cwFlashWriteWrn++;
  }

  if (i == FLASH_REPEATS)
  {
    cwFlashWriteErr++;
    return false;
  }
  else return true;
}



uint    GetFlashStatus(void)
{
  uint i = 0;

  if (cwFlashCompareErr   != 0) i |= 0x0001;
  if (cwFlashEraseErr != 0) i |= 0x0002;
  if (cwFlashReadErr  != 0) i |= 0x0004;
  if (cwFlashWriteErr != 0) i |= 0x0008;

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
void    TODO OutFlashReadStatus(void) { + add (++i > STATUS_REPEATS) + add cwFlashBusyWrn etc
  InitPushCRC();

  ReadStatus();
  PushChar(bStatusFlash);

  PushChar(ReadStatus());

  Output(sizeof(char)+sizeof(char));
}
*/
