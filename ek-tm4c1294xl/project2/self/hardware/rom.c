/*------------------------------------------------------------------------------
rom.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "../kernel/crc16.h"
#include "../kernel/log.h"
#include "../hardware/delay.h"
#include "../hardware/led.h"
#include "rom.h"



static char const       szBinFileSize[] = "BinFileSize    BinFileSize";



static ulong GetBinFileSize(void)
{
  combo32 cm;
  cm.mb4[0] = szBinFileSize[11];
  cm.mb4[1] = szBinFileSize[12];
  cm.mb4[2] = szBinFileSize[13];
  cm.mb4[3] = szBinFileSize[14];

  return cm.dw;
}


static uchar GetRomChar(uchar  i)
{
  ulong dwSize = GetBinFileSize();
  return dwSize == 0x20202020 ? 0 : HWREGB(dwSize + i);
}



uint GetROMChecksum(void)
{
  return GetRomChar(0)*0x100 + GetRomChar(1);
}


uint GetROMBuildNumber(void)
{
  return GetRomChar(2)*0x100 + GetRomChar(3);
}


timedate_t GetROMBuildTimeDate(void)
{
  timedate_t td;
  td.bSecond = GetRomChar(4);
  td.bMinute = GetRomChar(5);
  td.bHour   = GetRomChar(6);
  td.bDay    = GetRomChar(7);
  td.bMonth  = GetRomChar(8);
  td.bYear   = GetRomChar(9);
  return td;
}



void InitROM(void)
{
  ulong dwSize = GetBinFileSize();
  if (dwSize != 0x20202020)
  {
    dwSize += 2;

    ulong i = 0;

    InitCRC16();
    while (dwSize-- > 0)
    {
      CalcCRC16(HWREGB(i++));
    }

    if ((bCRCHi != 0) || (bCRCLo != 0))
    {
      IntMasterDisable();
      while (true)
      {
        OffLED0();
        OnLED1();
        DelayMilliSecond(500);

        OnLED0();
        OffLED1();
        DelayMilliSecond(500);
      }
    }
  }
}
