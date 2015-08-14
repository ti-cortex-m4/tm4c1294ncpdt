/*------------------------------------------------------------------------------
DEVICES.C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../display/display.h"



//                                         0123456789ABCDEF
message                 mpszDevices[bMAXDEVICES+1] = {
                                          ".למהול          ",
                                          ".ÑÝÒ-4ÒÌ        ",
                                          ".Ìונךףנטי-230   ",
                                          ".CC-301         ",
                                          ".ףסענמיסעגמ 4   ",
                                          ".ףסענמיסעגמ 5   ",
                                          ".ףסענמיסעגמ 6   ",
                                          ".ףסענמיסעגמ 7   ",
                                          ".ףסענמיסעגמ 8   ",
                                          ".ףסענמיסעגמ 9   ",
                                          ".ףסענמיסעגמ 10  ",
                                          ".ףסענמיסעגמ 11  ",
                                          ".ףסענמיסעגמ 12  ",
                                          ".ףסענמיסעגמ 13  ",
                                          ".ףסענמיסעגמ 14  ",
                                          ".ףסענמיסעגמ 15  ",
                                          ".ףסענמיסעגמ 16  ",
                                          ".ףסענמיסעגמ 17  ",
                                          ".ףסענמיסעגמ 18  ",
                                          ".ףסענמיסעגמ 19  ",
                                          ".ףסענמיסעגמ 20  ",
                                          ".ףסענמיסעגמ 21  ",
                                          ".ףסענמיסעגמ 22  ",
                                          ".ףסענמיסעגמ 23  ",
                                          ".ףסענמיסעגמ 24  ",
                                          ".ףסענמיסעגמ 25  ",
                                          ".CE301          "
                                      };

uchar const             mpbMaxLines[bMAXDEVICES+1] =
{ 1, 4, 4, 4, 4, 16, 64, 16, 4, 6, 1, 1, 4, 4, 1, 4, 4, 1, 1, 1, 1, 4, 4, 4, 1, 2, 2 };



bool    IsDevice(uchar  bDevice)
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
  (IsDevice(bDevice)) ? (szLo[15] = '+') : (szLo[15] = '-');
}
