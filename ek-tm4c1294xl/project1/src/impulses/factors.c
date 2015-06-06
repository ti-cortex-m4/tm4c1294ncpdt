/*------------------------------------------------------------------------------
FACTORS,C

 Коэффициенты по каналам
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../flash/files.h"
#include "factors.h"



file const              flTransEng = {TRANS_ENG, &mpdbTransEng, sizeof(double)*bCANALS};
file const              flTransCnt = {TRANS_CNT, &mpdbTransCnt, sizeof(double)*bCANALS};

file const              flPulseHou = {PULSE_HOU, &mpdbPulseHou, sizeof(double)*bCANALS};
file const              flPulseMnt = {PULSE_MNT, &mpdbPulseMnt, sizeof(double)*bCANALS};

file const              flCount = {COUNT, &mpdbCount, sizeof(double)*bCANALS};
file const              flLosse = {LOSSE, &mpdbLosse, sizeof(double)*bCANALS};
file const              flLevel = {LEVEL, &mpdbLevel, sizeof(double)*bCANALS};



void    InitFactors(void)
{
  LoadFile(&flTransEng);
  LoadFile(&flTransCnt);

  LoadFile(&flPulseHou);
  LoadFile(&flPulseMnt);

  LoadFile(&flCount);
  LoadFile(&flLosse);
  LoadFile(&flLevel);

  StartFactors();
}


void    ResetFactors(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpdbTransEng[c] = 1;
    mpdbPulseHou[c] = 500;

    mpdbCount[c] = 0;
    mpdbLosse[c] = 0;
  }

  for (c=0; c<bCANALS; c++)
  {
    mpdbPulseMnt[c] = mpdbPulseHou[c];
    mpdbLevel[c] = 1;

    mpdbTransCnt[c] = 1;
  }

  SaveFile(&flTransEng);
  SaveFile(&flTransCnt);

  SaveFile(&flPulseHou);
  SaveFile(&flPulseMnt);

  SaveFile(&flCount);
  SaveFile(&flLosse);
  SaveFile(&flLevel);
}



void    SaveFactors(void)
{
  SaveFile(&flTransEng);
  SaveFile(&flTransCnt);

  SaveFile(&flPulseHou);
  SaveFile(&flPulseMnt);

  SaveFile(&flCount);
  SaveFile(&flLosse);
  SaveFile(&flLevel);
}



static double GetLosse(uchar  ibCan)
{
  return 1 + mpdbLosse[ibCan];
}


void    StartFactors(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpdbValueEngHou[c] = (mpdbTransEng[c] / mpdbPulseHou[c]) * GetLosse(c);
    mpdbValueCntHou[c] = (mpdbTransCnt[c] / mpdbPulseHou[c]) * GetLosse(c);
    mpdbValueEngMnt[c] = (mpdbTransEng[c] / mpdbPulseMnt[c]) * GetLosse(c);
    mpdbValueCntMnt[c] = (mpdbTransCnt[c] / mpdbPulseMnt[c]) * GetLosse(c);
  }
}
