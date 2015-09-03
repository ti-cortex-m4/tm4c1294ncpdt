/*------------------------------------------------------------------------------
23x1024.С


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../memory/mem_nvram.h"
#include "../kernel/crc-16.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "nvram.h"
#include "23x1024.h"



// количество повторов
#define NVRAM_REPEATS   8



void NvramCharOutCRC(uchar  b)
{
  NvramCharOut(b);
  CalcCRC(b);
}


void    InitNvram(void)
{
 //Включение периферии
 HWREG(SYSCTL_RCGCGPIO) |= 0x00000020;//Запуск "F"

 DelayGPIO();

 //Для порта "F" (SPI+CE)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DIR)   |= 0x000E;//пины на передачу (PF0 на прием)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DEN)   |= 0x000F;//цифровой сигнал

 NvramStop();
}



bool    PushNvramBuff(ulong  dwAddr, uint  wSize)
{
  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  uint i;
  for (i=0; i<wSize; i++)
  {
    PushChar(NvramCharIn());
  }

  NvramStop();

  return true;
}


bool    ReadNvramBuff_Raw(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  NvramCharIn();
  NvramCharIn();
  NvramCharIn();

  NvramCharIn();
  NvramCharIn();

  uint i;
  for (i=0; i<wSize; i++)
  {
   *(pbBuff++) = NvramCharIn();
  }

  NvramStop();

  return true;
}


bool    WriteNvramBuff_Raw(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  NvramStart();

  NvramCharOut(0x02); // запись
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  InitCRC();

  NvramCharOutCRC(*((uchar*)(&dwAddr)+2));
  NvramCharOutCRC(*((uchar*)(&dwAddr)+1));
  NvramCharOutCRC(*((uchar*)(&dwAddr)+0));

  NvramCharOutCRC(wSize / 0x100);
  NvramCharOutCRC(wSize % 0x100);

  uint i;
  for (i=0; i<wSize; i++)
  {
    NvramCharOutCRC(*(pbBuff++));
  }

  NvramCharOutCRC(tiCurr.bSecond);
  NvramCharOutCRC(tiCurr.bMinute);
  NvramCharOutCRC(tiCurr.bHour);
  NvramCharOutCRC(tiCurr.bDay);
  NvramCharOutCRC(tiCurr.bMonth);
  NvramCharOutCRC(tiCurr.bYear);

  NvramCharOut(bCRCHi);
  NvramCharOut(bCRCLo);


  NvramStop();

  pbBuff -= wSize;

  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  NvramCharIn();
  NvramCharIn();
  NvramCharIn();

  NvramCharIn();
  NvramCharIn();

  bool f = true;
  for (i=0; i<wSize; i++)
  {
    if (*(pbBuff++) != NvramCharIn())
    {
      f = false;
      break;
    }
  }

  NvramStop();

  return f;
}


bool    FreeNvramBuff_Raw(ulong  dwAddr, uint  wSize)
{
  NvramStart();

  NvramCharOut(0x02); // запись
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  InitCRC();

  NvramCharOutCRC(*((uchar*)(&dwAddr)+2));
  NvramCharOutCRC(*((uchar*)(&dwAddr)+1));
  NvramCharOutCRC(*((uchar*)(&dwAddr)+0));

  NvramCharOutCRC(wSize / 0x100);
  NvramCharOutCRC(wSize % 0x100);

  uint i;
  for (i=0; i<wSize; i++)
  {
    NvramCharOutCRC(0);
  }

  NvramCharOutCRC(tiCurr.bSecond);
  NvramCharOutCRC(tiCurr.bMinute);
  NvramCharOutCRC(tiCurr.bHour);
  NvramCharOutCRC(tiCurr.bDay);
  NvramCharOutCRC(tiCurr.bMonth);
  NvramCharOutCRC(tiCurr.bYear);

  NvramCharOut(bCRCHi);
  NvramCharOut(bCRCLo);


  NvramStop();

  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  NvramCharIn();
  NvramCharIn();
  NvramCharIn();

  NvramCharIn();
  NvramCharIn();

  bool f = true;
  for (i=0; i<wSize; i++)
  {
    if (0 != NvramCharIn())
    {
      f = false;
      break;
    }
  }

  NvramStop();

  return f;
}



uchar   ReadNvramStatus(void)
{
  NvramStart();
  NvramCharOut(0x05);
  uchar b = NvramCharIn();
  NvramStop();

  return b;
}



bool    ReadNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  cdwNvramReadBuff++;

  uchar i;
  for (i=0; i<NVRAM_REPEATS; i++) {
    if (ReadNvramBuff_Raw(dwAddr, pbBuff, wSize) == true) break;
    cwNvramReadWrn++;
  }

  if (i == NVRAM_REPEATS) {
    cwNvramReadErr++;
    return false;
  } else {
    return true;
  }
}


bool    WriteNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  cdwNvramWriteBuff++;

  uchar i;
  for (i=0; i<NVRAM_REPEATS; i++) {
    if (WriteNvramBuff_Raw(dwAddr, pbBuff, wSize) == true) break;
    cwNvramWriteWrn++;
  }

  if (i == NVRAM_REPEATS) {
    cwNvramWriteErr++;
    return false;
  } else {
    return true;
  }
}


bool    FreeNvramBuff(ulong  dwAddr, uint  wSize)
{
  cdwNvramFreeBuff++;

  uchar i;
  for (i=0; i<NVRAM_REPEATS; i++) {
    if (FreeNvramBuff_Raw(dwAddr, wSize) == true) break;
    cwNvramFreeWrn++;
  }

  if (i == NVRAM_REPEATS) {
    cwNvramFreeErr++;
    return false;
  } else {
    return true;
  }
}



bool    Test1WriteNvramBuff(ulong  dwAddr, uint  wSize)
{
  NvramStart();

  NvramCharOut(0x02); // запись
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  uint i;
  for (i=0; i<wSize; i++)
  {
    NvramCharOutCRC(wSize % 0x100);
  }

  NvramStop();

  return true;
}


bool    Test1ReadNvramBuff(ulong  dwAddr, uint  wSize)
{
  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  bool f = true;

  uint i;
  for (i=0; i<wSize; i++)
  {
    if ((wSize % 0x100) != NvramCharIn())
    {
      f = false;
      break;
    }
  }

  NvramStop();

  return f;
}



bool    Test2WriteNvramBuff(ulong  dwAddr, uint  wSize, uchar  b)
{
  NvramStart();

  NvramCharOut(0x02); // запись
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  uint i;
  for (i=0; i<wSize; i++)
  {
    NvramCharOutCRC(b);
  }

  NvramStop();

  return true;
}


bool    Test2ReadNvramBuff(ulong  dwAddr, uint  wSize, uchar  b)
{
  NvramStart();

  NvramCharOut(0x03); // чтение
  NvramCharOut(*((uchar*)(&dwAddr)+2));
  NvramCharOut(*((uchar*)(&dwAddr)+1));
  NvramCharOut(*((uchar*)(&dwAddr)+0));

  bool f = true;

  uint i;
  for (i=0; i<wSize; i++)
  {
    if (b != NvramCharIn())
    {
      f = false;
      break;
    }
  }

  NvramStop();

  return f;
}



uint    GetNvramStatus(void)
{
  uint w = 0;

  if (cwNvramCompareErr != 0) w |= 0x0001;
  if (cwNvramFreeErr    != 0) w |= 0x0002;
  if (cwNvramReadErr    != 0) w |= 0x0004;
  if (cwNvramWriteErr   != 0) w |= 0x0008;

  return w;
}
