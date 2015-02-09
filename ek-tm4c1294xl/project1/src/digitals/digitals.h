/*------------------------------------------------------------------------------
DIGITALS.H


------------------------------------------------------------------------------*/

extern  file const              flDigitals;



void    InitDigitals(void);
void    ResetDigitals(void);

uchar   GetDigitalPort(uchar  ibCan);
uchar   GetDigitalPhone(uchar  ibCan);
uchar   GetDigitalDevice(uchar  ibCan);
uchar   GetDigitalAddress(uchar  ibCan);
uchar   GetDigitalLine(uchar  ibCan);
