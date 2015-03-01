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


file const              flTransEng = {FLS_TRANS_ENG, &mpreTransEng, sizeof(real)*bCANALS};
file const              flTransCnt = {FLS_TRANS_CNT, &mpreTransCnt, sizeof(real)*bCANALS};

file const              flPulseHou = {FLS_PULSE_HOU, &mprePulseHou, sizeof(real)*bCANALS};
file const              flPulseMnt = {FLS_PULSE_MNT, &mprePulseMnt, sizeof(real)*bCANALS};

file const              flCount = {FLS_COUNT, &mpreCount, sizeof(real)*bCANALS};
file const              flLosse = {FLS_LOSSE, &mpreLosse, sizeof(real)*bCANALS};
file const              flLevel = {FLS_LEVEL, &mpreLevelDiv, sizeof(real)*bCANALS};


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
    mpreLevelDiv[c] = 1;

    mpreTransCnt[c] = 1;                      // в нормальном режиме: 1
  }

  SaveFile(&flTransEng);
  SaveFile(&flTransCnt);

  SaveFile(&flPulseHou);
  SaveFile(&flPulseMnt);

  SaveFile(&flCount);
  SaveFile(&flLosse);
  SaveFile(&flLevel);
}



void    AddLosse(uchar  ibCan)
{
  reBuffA *= 1 + GetCanReal(mpreLosse,ibCan);
}


void    StartFactors(void)
{
uchar  ibCan;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    reBuffA = GetCanReal(mpreTransEng,ibCan) / GetCanReal(mprePulseHou,ibCan);
    AddLosse(ibCan);
    SetCanReal(mpreValueEngHou,ibCan,&reBuffA);

    reBuffA = GetCanReal(mpreTransCnt,ibCan) / GetCanReal(mprePulseHou,ibCan);
    AddLosse(ibCan);
    SetCanReal(mpreValueCntHou,ibCan,&reBuffA);

    reBuffA = GetCanReal(mpreTransEng,ibCan) / GetCanReal(mprePulseMnt,ibCan);
    AddLosse(ibCan);
    SetCanReal(mpreValueEngMnt,ibCan,&reBuffA);

    reBuffA = GetCanReal(mpreTransCnt,ibCan) / GetCanReal(mprePulseMnt,ibCan);
    AddLosse(ibCan);
    SetCanReal(mpreValueCntMnt,ibCan,&reBuffA);
  }
}
