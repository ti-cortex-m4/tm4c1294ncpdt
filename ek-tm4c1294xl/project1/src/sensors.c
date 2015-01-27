/*------------------------------------------------------------------------------
SENSORS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_ports.h"



ulong   GetMajDelay(uchar  ibPort) {
  return (ulong)1000*mpwMajInDelay[ibPort]/wFREQUENCY_T0;
}


ulong   GetMinDelay(uchar  ibPort) {
  return (ulong)1000*mpwMinInDelay[ibPort]/wFREQUENCY_T0;
}



uchar   GetDigitalPort(uchar  ibCanal) {
  return 0;
}


uchar   GetDigitalPhone(uchar  ibCanal) {
  return 0;
}


uchar   GetDigitalDevice(uchar  ibCanal) {
  return 0;
}


uchar   GetDigitalAddress(uchar  ibCanal) {
  return 0;
}


uchar   GetDigitalLine(uchar  ibCanal) {
  return 0;
}
