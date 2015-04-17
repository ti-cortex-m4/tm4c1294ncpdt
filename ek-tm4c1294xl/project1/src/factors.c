/*------------------------------------------------------------------------------
FACTORS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_factors.h"
#include        "include/flash.h"
#include        "flash/files.h"
#include        "engine.h"
#include        "energy.h"
#include        "factors.h"


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

    mpreTransCnt[c] = 1;                      // в нормальном режиме: 1
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
  real  re;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    re = mpreTransEng[c] / mprePulseHou[c];
    mpreValueEngHou[c] = re * AddLosse(c);

    re = mpreTransCnt[c] / mprePulseHou[c];
    mpreValueCntHou[c] = re * AddLosse(c);

    re = mpreTransEng[c] / mprePulseMnt[c];
    mpreValueEngMnt[c] = re * AddLosse(c);

    re = mpreTransCnt[c] / mprePulseMnt[c];
    mpreValueCntMnt[c] = re * AddLosse(c);
  }
}
