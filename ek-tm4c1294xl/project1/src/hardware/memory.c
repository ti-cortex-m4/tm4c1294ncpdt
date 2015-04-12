/*------------------------------------------------------------------------------
TODO MEMORY.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "driverlib/sysctl.h"



char const              szImageSize[] = "ImageSize    ";



void    InitCODE(void)
{
}



ulong   GetCODESize(void)
{
  return szImageSize[0];
}


uchar   GetCODE(uchar  i)
{
  return 0;
}


uint    GetCODEChecksum(void)
{
  return GetCODE(0)*0x100 + GetCODE(1);
}


uint    GetBuildNumber(void)
{
  return 10; //GetCODE(2)*0x100 + GetCODE(3);
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
