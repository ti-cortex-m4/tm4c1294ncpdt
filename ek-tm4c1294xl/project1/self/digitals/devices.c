/*------------------------------------------------------------------------------
DEVICES!C


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
                                          ".ЦЭ6850М        ",
                                          ".ЦЭ6823М        ",
                                          ".ПРТ-C4         ",
                                          ".устройство 16  ",
                                          ".устройство 17  ",
                                          ".устройство 18  ",
                                          ".ПИ-1.4         ",
                                          ".устройство 20  ",
                                          ".Elster A1140   ",
                                          ".СЕ304          ",
                                          ".устройство 23  ",
                                          ".СЕ102          ",
                                          ".устройство 25  ",
                                          ".СЕ301          ",
                                          ".МИРТЕК         ",
                                          ".СЕ303          ",
                                          ".Rovalant МЭС-1 ",
                                          ".Rovalant МЭС-3 ",
                                          ".СТК3 v48-49    ",
                                          ".СТК3/1 v51-54  ",
                                          ".СТК3 v16,18    ",
                                          ".ESM            ",
                                          ".СЕ102 NNCL2    ",
                                          ".СЕ301 NNCL2    ",
                                          ".СЕ303 NNCL2    ",
                                          ".СЕ318          ",
                                          ".СЕ318 S39      ",
                                          ".Меркурий-234   "
                                      };

uchar const             mpbMaxLines[bMAXDEVICES+1] =
{ 1, 4, 4, 4, 4, 16, 64, 16, 4, 6, 1, 1, 4, 4, 1, 4, 4, 1, 1, 1, 1, 4, 4, 4, 1, 2, 2, 1, 4, 4, 4, 6, 1, 1, 4, 1, 2, 4, 4, 4 };



bool    ValidDevice(uchar  bDevice)
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

#ifndef SKIP_D
    case 4:  return true;
#endif

#ifndef SKIP_E
    case 7:
    case 5:  return true;
#endif

#ifndef SKIP_F
    case 6:  return true;
#endif

#ifndef SKIP_G
    case 9:  return true;
#endif

#ifndef SKIP_H
    case 10: return true;
#endif

#ifndef SKIP_I
    case 11: return true;
#endif

#ifndef SKIP_K
    case 14:
    case 13: return true;
#endif

#ifndef SKIP_L
    case 16:
    case 17: return true;
#endif

#ifndef SKIP_M
    case 18: return true;
#endif

#ifndef SKIP_N
    case 19: return true;
#endif

#ifndef SKIP_O
    case 20: return true;
#endif

#ifndef SKIP_P
    case 21: return true;
#endif

#ifndef SKIP_Q
    case 22: return true;
#endif

#ifndef SKIP_R
    case 23: return true;
#endif

#ifndef SKIP_S
    case 24: return true;
#endif

#ifndef SKIP_T
    case 25: return true;
#endif

#ifndef SKIP_U
    case 26:
    case 28: return true;
#endif

#ifndef SKIP_V
    case 27: return true;
#endif

#ifndef SKIP_W
    case 29:
    case 30: return true;
#endif

#ifndef SKIP_31
    case 31: return true;
#endif

#ifndef SKIP_32
    case 32: return true;
#endif

#ifndef SKIP_33
    case 33: return true;
#endif

#ifndef SKIP_34
    case 34: return true;
#endif

#ifndef SKIP_35
    case 35: return true;
#endif

#ifndef SKIP_36
    case 36:
    case 37: return true;
#endif

#ifndef SKIP_38
    case 38:
    case 39: return true;
#endif

#ifndef SKIP_39
    case 39: return true;
#endif

    default: return false;
  }
}



void    ShowDeviceName(uchar  bDevice)
{
  ASSERT(bDevice <= bMAXDEVICES);

  ShowLo( mpszDevices[bDevice] );
  (ValidDevice(bDevice)) ? (szLo[15] = '+') : (szLo[15] = '-');
}
