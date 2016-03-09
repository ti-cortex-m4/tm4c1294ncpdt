/*------------------------------------------------------------------------------
serials.c

Заводские номера цифровых счетчиков
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../digitals/digitals.h"
#include "../display/display.h"
#include "../time/timedate.h"
#include "../time/delay.h"
#include "../time/rtc.h"
#include "serials.h"



bool                    fSerialsManual;
ulong                   mdwSerialValues[bCANALS];
time                    mtiSerialTimes[bCANALS];
bool                    mfSerialFlags[bCANALS];


cache const             chSerialsManual = {SERIALS_MANUAL, &fSerialsManual, sizeof(bool)};
cache const             chSerialValues = {SERIAL_VALUES, &mdwSerialValues, sizeof(mdwSerialValues)};
cache const             chSerialTimes = {SERIAL_TIMES, &mtiSerialTimes, sizeof(mtiSerialTimes)};
cache const             chSerialFlags = {SERIAL_FLAGS, &mfSerialFlags, sizeof(mfSerialFlags)};



void    InitSerials(void)
{
  LoadCacheBool(&chSerialsManual, false);
  LoadCache(&chSerialValues);
  LoadCache(&chSerialTimes);
  LoadCache(&chSerialFlags);
}


void    ResetSerials(void)
{
  SaveCacheBool(&chSerialsManual, false);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mdwSerialValues[c] = 0;
    mtiSerialTimes[c] = tiZero;
    mfSerialFlags[c] = false;
  }

  SaveCache(&chSerialValues);
  SaveCache(&chSerialTimes);
  SaveCache(&chSerialFlags);
}



void    ProcessSerial(uchar  ibDig, ulong  dwSerial)
{
  mdwSerialValues[c] = dw;
  SaveCache(&chSerialValues);

  mtiSerialTimes[c] = *GetCurrTimeDate();
  SaveCache(&chSerialTimes);

  mfSerialFlags[c] = true;
  SaveCache(&chSerialFlags);
}


void    ProcessSerials(uchar  ibDig, ulong  dwSerial)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (CompareLines(ibDig,c) == true)
    {
      mdwSerialValues[c] = dwSerial;
      mtiSerialTimes[c] = *GetCurrTimeDate();
      mfSerialFlags[c] = true;
    }
  }

  SaveCache(&chSerialValues);
  SaveCache(&chSerialTimes);
  SaveCache(&chSerialFlags);

  Clear();
  szLo[0] = '#';
  sprintf(szLo+4,"%9lu",dwSerial);

  DelayInf();
}
