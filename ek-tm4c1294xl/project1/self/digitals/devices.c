/*------------------------------------------------------------------------------
DEVICES.C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../display/display.h"



//                                         0123456789ABCDEF
message                 mpszDevices[bDEVICES+1] = {
                                          ".модем          ",
                                          ".СЭТ-4ТМ        ",
                                          ".Меркурий-230   ",
                                          ".CC-301         ",
                                          ".CE301          "
                                      };

uchar const             mpbMaxLines[bDEVICES+1] =
{ 1, 4, 4, 4, 2 };



bool    IsDevice(uchar  ibDevice)
{
  switch (ibDevice)
  {
    case 0:  return(1);

#ifndef SKIP_A
    case 15:
    case 1:  return(1);
#endif

#ifndef SKIP_B
    case 12:
    case 8:
    case 2:  return(1);
#endif

#ifndef SKIP_C
    case 3:  return(1);
#endif

#ifndef SKIP_U
    case 26: return(1);
#endif

    default: return(0);
  }
}



void    ShowDeviceName(uchar  ibDevice)
{
  if (ibDevice < bDEVICES+1)
  {
    ShowLo( mpszDevices[ibDevice] );  
    (IsDevice(ibDevice) == 1) ? (szLo[15] = '+') : (szLo[15] = '-');
  }
  else Error();          
}
