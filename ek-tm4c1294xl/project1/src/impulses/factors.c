/*------------------------------------------------------------------------------
FACTORS,C

 Коэффициенты по каналам
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../flash/files.h"
#include "factors.h"



file const              flTransEng = {TRANS_ENG, &mpreTransEng, sizeof(real)*bCANALS};
file const              flTransCnt = {TRANS_CNT, &mpreTransCnt, sizeof(real)*bCANALS};

file const              flPulseHou = {PULSE_HOU, &mprePulseHou, sizeof(real)*bCANALS};
file const              flPulseMnt = {PULSE_MNT, &mprePulseMnt, sizeof(real)*bCANALS};

file const              flCount = {COUNT, &mpreCount, sizeof(real)*bCANALS};
file const              flLosse = {LOSSE, &mpreLosse, sizeof(real)*bCANALS};
file const              flLevelDiv = {LEVEL, &mpreLevelDiv, sizeof(real)*bCANALS};



void    InitFactors(void)
{
  LoadFile(&flTransEng);
  LoadFile(&flTransCnt);

  LoadFile(&flPulseHou);
  LoadFile(&flPulseMnt);

  LoadFile(&flCount);
  LoadFile(&flLosse);
  LoadFile(&flLevelDiv);

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
    mpreLevelDiv[c] = 1;

    mpreTransCnt[c] = 1; // в нормальном режиме равен 1
  }

  SaveFile(&flTransEng);
  SaveFile(&flTransCnt);

  SaveFile(&flPulseHou);
  SaveFile(&flPulseMnt);

  SaveFile(&flCount);
  SaveFile(&flLosse);
  SaveFile(&flLevelDiv);
}



void    SaveFactors(void)
{
  SaveFile(&flTransEng);
  SaveFile(&flTransCnt);

  SaveFile(&flPulseHou);
  SaveFile(&flPulseMnt);

  SaveFile(&flCount);
  SaveFile(&flLosse);
  SaveFile(&flLevelDiv);
}



real    AddLosse(uchar  c)
{
  return 1 + mpreLosse[c];
}


void    StartFactors(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpreValueEngHou[c] = (mpreTransEng[c] / mprePulseHou[c]) * AddLosse(c);
    mpreValueCntHou[c] = (mpreTransCnt[c] / mprePulseHou[c]) * AddLosse(c);
    mpreValueEngMnt[c] = (mpreTransEng[c] / mprePulseMnt[c]) * AddLosse(c);
    mpreValueCntMnt[c] = (mpreTransCnt[c] / mprePulseMnt[c]) * AddLosse(c);
  }
}
