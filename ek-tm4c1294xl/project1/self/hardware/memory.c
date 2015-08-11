/*------------------------------------------------------------------------------
TODO MEMORY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "../display/lcd.h"
#include "../display/messages.h"
#include "../kernel/crc-16.h"



char const              szImageSize[] = "ImageSize    ImageSize";



ulong   GetFileSize(void)
{
  combo32 co;
  co.mpbBuff[0] = szImageSize[9];
  co.mpbBuff[1] = szImageSize[10];
  co.mpbBuff[2] = szImageSize[11];
  co.mpbBuff[3] = szImageSize[12];

  return co.dwBuff;
}


uchar   GetCODE(uchar  i)
{
  ulong dwFileSize = GetFileSize();
  return dwFileSize == 0x20202020 ? 0 : HWREGB(dwFileSize + i);
}


uint    GetRomChecksum(void)
{
  return GetCODE(0)*0x100 + GetCODE(1);
}


uint    GetBuildNumber(void)
{
  return GetCODE(2)*0x100 + GetCODE(3);
}


uchar   GetBuildDate_Second(void) { return GetCODE(4); }
uchar   GetBuildDate_Minute(void) { return GetCODE(5); }
uchar   GetBuildDate_Hour(void)   { return GetCODE(6); }
uchar   GetBuildDate_Day(void)    { return GetCODE(7); }
uchar   GetBuildDate_Month(void)  { return GetCODE(8); }
uchar   GetBuildDate_Year(void)   { return GetCODE(9); }



void    Restart(void)
{
  SysCtlReset();
}



void    InitCODE(void)
{
  ulong dwFileSize = GetFileSize();
  if (dwFileSize != 0x20202020)
  {
    ulong i = 0;
    ulong dwSize = dwFileSize + 2;

    InitCRC();
    while (dwSize-- > 0) CalcCRC(HWREGB(i++));

    if ((bCRCHi != 0) || (bCRCLo != 0)) TestError(szBadCODE);
  }
}
