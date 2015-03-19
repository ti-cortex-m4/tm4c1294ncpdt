/*------------------------------------------------------------------------------
DIGITALS.C

 Цифровые счетчики
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals0.h"
#include        "../memory/mem_digitals.h"
#include        "../display/display.h"
#include        "../flash/files.h"
#include        "digitals.h"



file const              flDigitals = {FLS_DIGITALS, &mpdiDigital, sizeof(digital)*bCANALS};

file const              flEnblKeys = {FLS_ENBL_KEYS, &boEnblKeys, sizeof(boolean)};
file const              flKeys = {FLS_KEYS, &mpphKeys, sizeof(phone)*bCANALS};

file const              flAddress1 = {FLS_ADDRESS1, &mpdwAddress1, sizeof(ulong)*bCANALS};
file const              flAddress2 = {FLS_ADDRESS2, &mpdwAddress2, sizeof(ulong)*bCANALS};



void    InitDigitals(void)
{
  LoadFile(&flDigitals);
  MakeDigitalsMask();

  LoadFile(&flEnblKeys);

  LoadFile(&flKeys);

  LoadFile(&flAddress1);
  LoadFile(&flAddress2);
}


void    ResetDigitals(void)
{
  memset(&mpdiDigital, 0, sizeof(mpdiDigital));
  SaveFile(&flDigitals);

  boEnblKeys = FALSE;
  SaveFile(&flEnblKeys);

  uchar c;
  for (c=0; c<bCANALS; c++)
    strcpy((char *)mpphKeys[c].szNumber, "0");

  SaveFile(&flKeys);

  for (c=0; c<bCANALS; c++)
  {
    mpdwAddress1[c] = 0;
    mpdwAddress2[c] = 0;
  }

  SaveFile(&flAddress1);
  SaveFile(&flAddress2);
}



void    LoadCurrDigital(uchar  ibCan)
{
  diCurr = mpdiDigital[ ibCan ];
}


void    LoadPrevDigital(uchar  ibCan)
{
  diPrev = mpdiDigital[ ibCan ];
}


bool    CompareCurrPrevLines(uchar  ibDig, uchar  ibCan)
{
  return( (diPrev.ibPort   == diCurr.ibPort)   &&
          (diPrev.ibPhone  == diCurr.ibPhone)  &&
          (diPrev.bDevice  == diCurr.bDevice)  &&
          (diPrev.bAddress == diCurr.bAddress) &&
          ((ibDig == ibCan) || (boSeparateCan == FALSE)) );
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



bool    TrueDigital(digital  *pdi)
{
  return true;
}


void    SetDigital(uchar  ibCan, digital  *pdi)
{
  mpdiDigital[ibCan] = *pdi;
  SaveFile(&flDigitals);
}


void    MakeDigitalsMask(void)
{
uchar   i;

  wDigitalsMask = 0x0000;
  for (i=0; i<16; i++)
  {
    if (GetDigitalDevice(i) == 0)
      wDigitalsMask |= (1 << i);
  }
}



void    ShowDigital(uchar  ibCan)
{
  sprintf(szLo,"%1u.%02u.%02u.%03u.%02u  ",
               GetDigitalPort(ibCan)+1,
               GetDigitalPhone(ibCan),
               GetDigitalDevice(ibCan),
               GetDigitalAddress(ibCan),
               GetDigitalLine(ibCan)+1);

  sprintf(szHi+14,"%02u",ibCan+1);
  (mpboEnblCan[ibCan]) ? (szHi[13] = '+') : (szHi[13] = '-');
}


void    ShowDigitalNumber(uchar  ibDig)
{
  ShowHi(szClear);
  sprintf(szHi,"Канал: %-2u",ibDig+1);
}


void    ShowCanalNumber(uchar  ibCan)
{
  ShowHi(szClear);
  sprintf(szHi,"Канал: %-2u",ibCan+1);
}


void    ShowPort(uchar  ibPort)
{
  ShowHi(szClear);
  sprintf(szHi,"Порт: %u",ibPort+1);
}
