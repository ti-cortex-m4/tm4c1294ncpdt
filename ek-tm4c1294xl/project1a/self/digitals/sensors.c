/*------------------------------------------------------------------------------
SENSORS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../digitals/digitals.h"



ulong   GetMajorDelay(uchar  ibPort) {
  return (ulong)1000*mpwMajorInDelay[ibPort]/wFREQUENCY_T0;
}


ulong   GetMinorDelay(uchar  ibPort) {
  return (ulong)1000*mpwMinorInDelay[ibPort]/wFREQUENCY_T0;
}



bool    IsPulseCanal(uchar  ibCan)
{
  return (ibCan < 16) && (GetDigitalDevice(ibCan) == 0);
}
