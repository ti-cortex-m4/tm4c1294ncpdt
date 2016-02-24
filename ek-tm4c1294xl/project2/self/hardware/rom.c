/*------------------------------------------------------------------------------
rom,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_types.h"
#include "../kernel/crc16.h"
#include "../kernel/log.h"
#include "rom.h"



static char const       szBinFileSize[] = "BinFileSize    BinFileSize";



ulong   GetBinFileSize(void)
{
  combo32 co;
  co.mpbBuff[0] = szBinFileSize[11];
  co.mpbBuff[1] = szBinFileSize[12];
  co.mpbBuff[2] = szBinFileSize[13];
  co.mpbBuff[3] = szBinFileSize[14];

  return co.dwBuff;
}


uchar   GetRomChar(uchar  i)
{
  ulong dwFileSize = GetBinFileSize();
  return dwFileSize == 0x20202020 ? 0 : HWREGB(dwFileSize + i);
}


uint    GetRomChecksum(void)
{
  return GetRomChar(0)*0x100 + GetRomChar(1);
}


uint    GetBuildNumber(void)
{
  return GetRomChar(2)*0x100 + GetRomChar(3);
}


uchar   GetBuildDate_Second(void) { return GetRomChar(4); }
uchar   GetBuildDate_Minute(void) { return GetRomChar(5); }
uchar   GetBuildDate_Hour(void)   { return GetRomChar(6); }
uchar   GetBuildDate_Day(void)    { return GetRomChar(7); }
uchar   GetBuildDate_Month(void)  { return GetRomChar(8); }
uchar   GetBuildDate_Year(void)   { return GetRomChar(9); }


/*
void    Restart(void)
{
  SysCtlReset();
}
*/


void    InitROM(void)
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
    }
  }
}

