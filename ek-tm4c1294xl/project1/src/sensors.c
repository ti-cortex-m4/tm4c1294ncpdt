/*------------------------------------------------------------------------------
SENSORS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_ports.h"
#include        "digitals/digitals.h"



ulong   GetMajDelay(uchar  ibPort) {
  return (ulong)1000*mpwMajInDelay[ibPort]/wFREQUENCY_T0;
}


ulong   GetMinDelay(uchar  ibPort) {
  return (ulong)1000*mpwMinInDelay[ibPort]/wFREQUENCY_T0;
}



bool    IsPulseCanal(uchar  ibCan)
{
  return (ibCan < 16) && (GetDigitalDevice(ibCan) == 0);
}
