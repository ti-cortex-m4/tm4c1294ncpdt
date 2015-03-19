/*------------------------------------------------------------------------------
DIGITALS.H


------------------------------------------------------------------------------*/

extern  file const              flDigitals;

extern  file const              flEnblKeys;
extern  file const              flKeys;



void    InitDigitals(void);
void    ResetDigitals(void);

void    LoadCurrDigital(uchar  ibCan);
void    LoadPrevDigital(uchar  ibCan);
bool    CompareCurrPrevLines(uchar  ibDig, uchar  ibCan);

uchar   GetDigitalPort(uchar  ibCan);
uchar   GetDigitalPhone(uchar  ibCan);
uchar   GetDigitalDevice(uchar  ibCan);
uchar   GetDigitalAddress(uchar  ibCan);
uchar   GetDigitalLine(uchar  ibCan);

bool    TrueDigital(digital  *pdi);
void    SetDigital(uchar  ibCan, digital  *pdi);

void    MakeDigitalsMask(void);

void    ShowDigital(uchar  ibCan);
void    ShowDigitalNumber(uchar  ibDig);
void    ShowCanalNumber(uchar  ibCan);
void    ShowPort(uchar  ibPort);
