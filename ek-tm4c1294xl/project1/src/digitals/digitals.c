/*------------------------------------------------------------------------------
DIGITALS.C

 Цифровые счетчики
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../display/display.h"
#include        "../flash/files.h"



file const              flDigitals = {wFLA_GAPS, &mpdiDigital, sizeof(digital)*bCANALS};



void    InitDigitals(void)
{
  LoadFile(&flDigitals);
}


void    ResetDigitals(void)
{
  memset(&mpdiDigital, 0, sizeof(mpdiDigital));
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



void    SetDigital(uchar  ibCan, digital  *pdi)
{
  mpdiDigital[ibCan] = *pdi;
}



void    MakeDigitals(void)
{
uchar   i;

  wDigitals = 0x0000;
  for (i=0; i<16; i++)
  {
    if (GetDigitalDevice(i) == 0)
      wDigitals |= (1 << i);
  }
}



void    ShowDigital(uchar  i)
{
  sprintf(szLo,"%1u.%02u.%02u.%03u.%02u  ",
               GetDigitalPort(i)+1,
               GetDigitalPhone(i),
               GetDigitalDevice(i),
               GetDigitalAddress(i),
               GetDigitalLine(i)+1);

  sprintf(szHi+14,"%02u",i+1);
  (mpboEnblCan[i]) ? (szHi[13] = '+') : (szHi[13] = '-');
}
