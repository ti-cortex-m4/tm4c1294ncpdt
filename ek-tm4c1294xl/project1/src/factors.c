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


file const              flTransEng = {DF_TRANS_ENG, &mpreTransEng, sizeof(real)*bCANALS, FOR_REAL};
file const              flTransCnt = {DF_TRANS_CNT, &mpreTransCnt, sizeof(real)*bCANALS, FOR_REAL};

file const              flPulseHou = {DF_PULSE_HOU, &mprePulseHou, sizeof(real)*bCANALS, FOR_REAL};
file const              flPulseMnt = {DF_PULSE_MNT, &mprePulseMnt, sizeof(real)*bCANALS, FOR_REAL};

file const              flCount = {DF_COUNT, &mpreCount, sizeof(real)*bCANALS, FOR_REAL};
file const              flLosse = {DF_LOSSE, &mpreLosse, sizeof(real)*bCANALS, FOR_REAL};
file const              flLevel = {DF_LEVEL, &mpreLevelDiv, sizeof(real)*bCANALS, FOR_REAL};


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
