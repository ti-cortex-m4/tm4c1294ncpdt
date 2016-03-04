/*------------------------------------------------------------------------------
DIGITALS!H


------------------------------------------------------------------------------*/

#include "../memory/mem_digitals.h"



extern  cache const             chDigitals;
extern  cache const             chEnblCan;

extern  cache const             chEnblKeys;
extern  cache const             chKeys;

extern  cache const             chAddress1;
extern  cache const             chAddress2;

extern  cache const             chSerialsManual;
extern  cache const             chSerialValues;
extern  cache const             chSerialFlags;



void    InitDigitals(void);
void    ResetDigitals(void);

void    LoadCurrDigital(uchar  ibCan);
void    LoadPrevDigital(uchar  ibCan);
bool    CompareCurrPrevLines(uchar  ibDig, uchar  ibCan);
bool    CompareLines(uchar  ibDig, uchar  ibCan);
bool    SkipLine(uchar  ibDig, uchar  ibLine);

uchar   GetDigitalPort(uchar  ibCan);
uchar   GetDigitalPhone(uchar  ibCan);
uchar   GetDigitalDevice(uchar  ibCan);
uchar   GetDigitalAddress(uchar  ibCan);
uchar   GetDigitalLine(uchar  ibCan);

bool    TrueDigital(digital  *pdi);
void    SetDigital(uchar  ibCan, digital  *pdi);

void    MakeDigitalsMask(void);
