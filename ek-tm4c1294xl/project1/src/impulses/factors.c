/*------------------------------------------------------------------------------
FACTORS,C

 Коэффициенты по каналам
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../flash/files.h"
#include "factors.h"



file const              flTransEng = {TRANS_ENG, &mpreTransEng, sizeof(float)*bCANALS};
file const              flTransCnt = {TRANS_CNT, &mpreTransCnt, sizeof(float)*bCANALS};

file const              flPulseHou = {PULSE_HOU, &mprePulseHou, sizeof(float)*bCANALS};
file const              flPulseMnt = {PULSE_MNT, &mprePulseMnt, sizeof(float)*bCANALS};

file const              flCount = {COUNT, &mpreCount, sizeof(float)*bCANALS};
file const              flLosse = {LOSSE, &mpreLosse, sizeof(float)*bCANALS};
file const              flLevel = {LEVEL, &mpreLevel, sizeof(float)*bCANALS};



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
uchar   c;

  for (c=0; c<bCANALS; c++)
  {
    mpreTransEng[c] = 1;
    mprePulseHou[c] = 500;

    mpreCount[c] = 0;
    mpreLosse[c] = 0;
  }

  for (c=0; c<bCANALS; c++)
  {
    mprePulseMnt[c] = mprePulseHou[c];
    mpreLevel[c] = 1;

    mpreTransCnt[c] = 1; // в нормальном режиме равен 1
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



static float GetLosse(uchar  ibCan)
{
  return 1 + mpreLosse[ibCan];
}


void    StartFactors(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpreValueEngHou[c] = (mpreTransEng[c] / mprePulseHou[c]) * GetLosse(c);
    mpreValueCntHou[c] = (mpreTransCnt[c] / mprePulseHou[c]) * GetLosse(c);
    mpreValueEngMnt[c] = (mpreTransEng[c] / mprePulseMnt[c]) * GetLosse(c);
    mpreValueCntMnt[c] = (mpreTransCnt[c] / mprePulseMnt[c]) * GetLosse(c);
  }
}
