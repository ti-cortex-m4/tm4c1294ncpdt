/*------------------------------------------------------------------------------
DIGITALS.H


------------------------------------------------------------------------------*/

#include "../memory/mem_digitals.h"



extern  file const              flDigitals;

extern  file const              flEnblKeys;
extern  file const              flKeys;

extern  file const              flAddress1;
extern  file const              flAddress2;



void    InitDigitals(void);
void    ResetDigitals(void);

void    LoadCurrDigital(uchar  ibCan);
void    LoadPrevDigital(uchar  ibCan);
bool    CompareCurrPrevLines(uchar  ibDig, uchar  ibCan);
bool    CompareLines(uchar  ibDig, uchar  ibCan);

uchar   GetDigitalPort(uchar  ibCan);
uchar   GetDigitalPhone(uchar  ibCan);
uchar   GetDigitalDevice(uchar  ibCan);
uchar   GetDigitalAddress(uchar  ibCan);
uchar   GetDigitalLine(uchar  ibCan);

bool    TrueDigital(digital  *pdi);
void    SetDigital(uchar  ibCan, digital  *pdi);

void    MakeDigitalsMask(void);
