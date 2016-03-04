/*------------------------------------------------------------------------------
DIGITALS!C

 Цифровые счетчики
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals0.h"
#include "../memory/mem_digitals.h"
#include "../nvram/cache.h"
#include "sensors.h"
#include "digitals.h"



cache const             chDigitals = {DIGITALS, &mpdiDigital, sizeof(mpdiDigital)};
cache const             chEnblCan = {ENBL_CAN, &mpboEnblCan, sizeof(mpboEnblCan)};

cache const             chEnblKeys = {ENBL_KEYS, &boEnblKeys, sizeof(bool)};
cache const             chKeys = {KEYS, &mpphKeys, sizeof(mpphKeys)};

cache const             chAddress1 = {ADDRESS1, &mpdwAddress1, sizeof(mpdwAddress1)};
cache const             chAddress2 = {ADDRESS2, &mpdwAddress2, sizeof(mpdwAddress2)};

cache const             chSerialValues = {SERIAL_VALUES, &mdwSerialValues, sizeof(mdwSerialValues)};
cache const             chSerialFlags = {SERIAL_FLAGS, &mfSerialFlags, sizeof(mfSerialFlags)};



void    InitDigitals(void)
{
  LoadCache(&chDigitals);
  MakeDigitalsMask();

  LoadCache(&chEnblCan);

  LoadCache(&chEnblKeys);
  LoadCache(&chKeys);

  LoadCache(&chAddress1);
  LoadCache(&chAddress2);

  LoadCache(&chSerialValues);
  LoadCache(&chSerialFlags);
}


void    ResetDigitals(void)
{
  memset(&mpdiDigital, 0, sizeof(mpdiDigital));
  SaveCache(&chDigitals);


  uchar c;
  for (c=0; c<bCANALS; c++)
    mpboEnblCan[c] = true;

  SaveCache(&chEnblCan);


  boEnblKeys = false;
  SaveCache(&chEnblKeys);


  memset(&mpphKeys, 0, sizeof(mpphKeys));

  for (c=0; c<bCANALS; c++)
    mpphKeys[c].szLine[0] = '0';

  SaveCache(&chKeys);


  for (c=0; c<bCANALS; c++)
  {
    mpdwAddress1[c] = 0;
    mpdwAddress2[c] = 0;
  }

  SaveCache(&chAddress1);
  SaveCache(&chAddress2);


  for (c=0; c<bCANALS; c++)
  {
    mdwSerialValues[c] = 0;
    mfSerialFlags[c] = false;
  }

  SaveCache(&chSerialValues);
  SaveCache(&chSerialFlags);
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
          ((ibDig == ibCan) || (boSeparateCan == false)) );
}


bool    CompareLines(uchar  ibDig, uchar  ibCan)
{
  return( (GetDigitalPort(ibDig)    == GetDigitalPort(ibCan))   &&
          (GetDigitalPhone(ibDig)   == GetDigitalPhone(ibCan))  &&
          (GetDigitalDevice(ibDig)  == GetDigitalDevice(ibCan))  &&
          (GetDigitalAddress(ibDig) == GetDigitalAddress(ibCan)) &&
          ((ibDig == ibCan) || (boSeparateCan == false)) );
}


bool    SkipLine(uchar  ibDig, uchar  ibLine)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if( (GetDigitalPort(ibDig)    == GetDigitalPort(c))    &&
        (GetDigitalPhone(ibDig)   == GetDigitalPhone(c))   &&
        (GetDigitalDevice(ibDig)  == GetDigitalDevice(c))  &&
        (GetDigitalAddress(ibDig) == GetDigitalAddress(c)) &&
        (ibLine                   == GetDigitalLine(c))) return false;
  }

  return true;
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
  SaveCache(&chDigitals);
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
