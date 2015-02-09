/*------------------------------------------------------------------------------
DIGITALS.C

 Цифровые счетчики
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../flash/files.h"



file const              flDigitals = {wFLA_GAPS, &mpdiDigital, sizeof(digital)*bCANALS};



void    InitDigitals(void)
{
	LoadFile(&flDigitals);
}


void    ResetDigitals(void)
{
  memset(&gaGaps, 0, sizeof(gaGaps));
	SaveFile(&flDigitals);
}


uchar   GetDigitalPort(uchar  ibCan) {
  return mpdiDigital[ibCan].ibPort;
}


uchar   GetDigitalPhone(uchar  ibCan) {
  return mpdiDigital[ibCan].ibPhone;
}


uchar   GetDigitalDevice(uchar  ibCan) {
  return mpdiDigital[ibCan].bDevice;
}


uchar   GetDigitalAddress(uchar  ibCan) {
  return mpdiDigital[ibCan].bAddress;
}


uchar   GetDigitalLine(uchar  ibCan) {
  return mpdiDigital[ibCan].ibLine;
}



void    ShowDigital(uchar  i)
{
  sprintf(szLo,"%1bu.%02bu.%02bu.%03bu.%02bu  ",
               GetDigitalPort(i)+1,
               GetDigitalPhone(i),
               GetDigitalDevice(i),
               GetDigitalAddress(i),
               GetDigitalLine(i)+1);

  sprintf(szHi+14,"%02bu",i+1);
  (mpboEnblCan[i] == boTrue) ? (szHi[13] = '+') : (szHi[13] = '-');
}
