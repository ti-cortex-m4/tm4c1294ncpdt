/*------------------------------------------------------------------------------
DEVICES.C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../display/display.h"



//                                         0123456789ABCDEF
message                 mpszDevices[bMAXDEVICES+1] = {
                                          ".модем          ",
                                          ".СЭТ-4ТМ        ",
                                          ".Меркурий-230   ",
                                          ".CC-301         ",
                                          ".устройство 4   ",
                                          ".устройство 5   ",
                                          ".устройство 6   ",
                                          ".устройство 7   ",
                                          ".ПРТ-M230       ",
                                          ".устройство 9   ",
                                          ".устройство 10  ",
                                          ".устройство 11  ",
                                          ".Меркурий-230 ! ",
                                          ".устройство 13  ",
                                          ".устройство 14  ",
                                          ".ПРТ-C4         ",
                                          ".устройство 16  ",
                                          ".устройство 17  ",
                                          ".устройство 18  ",
                                          ".устройство 19  ",
                                          ".устройство 20  ",
                                          ".устройство 21  ",
                                          ".устройство 22  ",
                                          ".устройство 23  ",
                                          ".СЕ102          ",
                                          ".устройство 25  ",
                                          ".СЕ301          "
                                      };

uchar const             mpbMaxLines[bMAXDEVICES+1] =
{ 1, 4, 4, 4, 4, 16, 64, 16, 4, 6, 1, 1, 4, 4, 1, 4, 4, 1, 1, 1, 1, 4, 4, 4, 1, 2, 2 };



bool    IsValidDevice(uchar  bDevice)
{
  ASSERT(bDevice <= bMAXDEVICES);

  switch (bDevice)
  {
    case 0:  return true;

#ifndef SKIP_A
    case 15:
    case 1:  return true;
#endif

#ifndef SKIP_B
    case 12:
    case 8:
    case 2:  return true;
#endif

#ifndef SKIP_C
    case 3:  return true;
#endif

#ifndef SKIP_P
    case 21: return true;
#endif

#ifndef SKIP_S
    case 24: return true;
#endif

#ifndef SKIP_U
    case 26: return true;
#endif

    default: return false;
  }
}



void    ShowDeviceName(uchar  bDevice)
{
  ASSERT(bDevice <= bMAXDEVICES);

  ShowLo( mpszDevices[bDevice] );
  (IsValidDevice(bDevice)) ? (szLo[15] = '+') : (szLo[15] = '-');
}
