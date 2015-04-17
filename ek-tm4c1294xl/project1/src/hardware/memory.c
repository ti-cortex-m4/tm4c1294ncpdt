/*------------------------------------------------------------------------------
TODO MEMORY.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "inc/hw_types.h"
#include        "driverlib/sysctl.h"



char const              szImageSize[] = "ImageSize    ImageSize";



void    InitCODE(void)
{
//  ulong i = 0;
//  ulong dwSize = GetFileSize() + 2;
//
//  InitCRC();
//  while (dwSize-- > 0) CalcCRC(HWREGB(i++));
//
//  if ((bCRCHi != 0) || (bCRCLo != 0)) TestError(szBadCODE);
}



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
  return HWREGB(GetFileSize() + i);
}


uint    GetCODEChecksum(void)
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
