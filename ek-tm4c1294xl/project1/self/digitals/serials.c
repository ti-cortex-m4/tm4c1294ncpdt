/*------------------------------------------------------------------------------
SERIALS.C

 Заводские номера цифровых счетчиков
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../digitals/digitals.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "serials.h"



bool                    fSerialsManual;
ulong                   mdwSerialValues[bCANALS];
bool                    mfSerialFlags[bCANALS];


cache const             chSerialsManual = {SERIALS_MANUAL, &fSerialsManual, sizeof(bool)};
cache const             chSerialValues = {SERIAL_VALUES, &mdwSerialValues, sizeof(mdwSerialValues)};
cache const             chSerialFlags = {SERIAL_FLAGS, &mfSerialFlags, sizeof(mfSerialFlags)};



void    InitSerials(void)
{
  LoadCacheBool(&chSerialsManual, false);
  LoadCache(&chSerialValues);
  LoadCache(&chSerialFlags);
}


void    ResetSerials(void)
{
  SaveCacheBool(&chSerialsManual, false);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mdwSerialValues[c] = 0;
    mfSerialFlags[c] = false;
  }

  SaveCache(&chSerialValues);
  SaveCache(&chSerialFlags);
}



void    ProcessSerial(uchar  ibDig, ulong  dwSerial)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (CompareLines(ibDig,c) == true)
    {
      mdwSerialValues[c] = dwSerial;
      mfSerialFlags[c] = true;
    }
  }

  SaveCache(&chSerialValues);
  SaveCache(&chSerialFlags);

  Clear();
  szLo[0] = '#';
  sprintf(szLo+4,"%9lu",dwSerial);

  DelayInf();
}
