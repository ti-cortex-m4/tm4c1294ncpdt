/*------------------------------------------------------------------------------
SENSORS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_ports.h"



ulong   GetMajDelay(uchar  i)
{
  return( (ulong)1000*mpwMajInDelay[i]/wFREQUENCY_T0 );
}


ulong   GetMinDelay(uchar  i)
{
  return( (ulong)1000*mpwMinInDelay[i]/wFREQUENCY_T0 );
}
