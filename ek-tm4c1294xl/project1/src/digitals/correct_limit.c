/*------------------------------------------------------------------------------
CORRECT_LIMIT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



void    SetCorrectLimit(uchar  ibPrt)
{
//  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  ibPrt)
{
//  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM) SetCorrectLimit(ibPrt);
//  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM) mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}


uchar   MinorCorrect(void)
{
  return 5; //mpbCorrectLimit[diCurr.ibPort];
}
