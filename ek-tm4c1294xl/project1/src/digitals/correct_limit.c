/*------------------------------------------------------------------------------
CORRECT_LIMIT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../nvram/cache.h"
#include "correct_limit.h"



cache const             chCorrectLimit = {CORRECT_LIMIT, &mpbCorrectLimit, sizeof(mpbCorrectLimit)};



void    InitCorrectLimit(void)
{
  LoadCache(&chCorrectLimit);
}


void    ResetCorrectLimit(void)
{
  SaveCache(&chCorrectLimit);
}



void    SetCorrectLimit(uchar  ibPrt)
{
  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
  SaveCache(&chCorrectLimit);
}


void    CheckCorrectLimit(uchar  ibPrt)
{
  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM)
  {
    SetCorrectLimit(ibPrt);
  }

  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM)
  {
    mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
    SaveCache(&chCorrectLimit);
  }
}


void    MakeCorrectLimit(uchar  ibPort, uchar  bDevice)
{
  if (bDevice == 24)
  {
    mpbCorrectLimit[ibPort] = bCORRECT_DEVICE_S;
  }

  SaveCache(&chCorrectLimit);
}


uchar   GetCorrectLimit(void)
{
  return mpbCorrectLimit[diCurr.ibPort];
}
