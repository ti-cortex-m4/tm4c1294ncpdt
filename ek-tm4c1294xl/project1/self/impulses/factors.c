/*------------------------------------------------------------------------------
FACTORS,C

 Коэффициенты по каналам
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "factors.h"



cache const             chTransEng = {TRANS_ENG, &mpdbTransEng, sizeof(double)*bCANALS};
cache const             chTransCnt = {TRANS_CNT, &mpdbTransCnt, sizeof(double)*bCANALS};

cache const             chPulseHou = {PULSE_HOU, &mpdbPulseHou, sizeof(double)*bCANALS};
cache const             chPulseMnt = {PULSE_MNT, &mpdbPulseMnt, sizeof(double)*bCANALS};

cache const             chCount = {COUNT, &mpdbCount, sizeof(double)*bCANALS};
cache const             chLosse = {LOSSE, &mpdbLosse, sizeof(double)*bCANALS};
cache const             chLevel = {LEVEL, &mpdbLevel, sizeof(double)*bCANALS};



void    InitFactors(void)
{
  LoadCache(&chTransEng);
  LoadCache(&chTransCnt);

  LoadCache(&chPulseHou);
  LoadCache(&chPulseMnt);

  LoadCache(&chCount);
  LoadCache(&chLosse);
  LoadCache(&chLevel);

  if (enGlobal == GLB_WORK)
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

  SaveCache(&chTransEng);
  SaveCache(&chTransCnt);

  SaveCache(&chPulseHou);
  SaveCache(&chPulseMnt);

  SaveCache(&chCount);
  SaveCache(&chLosse);
  SaveCache(&chLevel);
}



void    SaveFactors(void)
{
  SaveCache(&chTransEng);
  SaveCache(&chTransCnt);

  SaveCache(&chPulseHou);
  SaveCache(&chPulseMnt);

  SaveCache(&chCount);
  SaveCache(&chLosse);
  SaveCache(&chLevel);
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
