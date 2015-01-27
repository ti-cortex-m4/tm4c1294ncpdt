/*------------------------------------------------------------------------------
ENGINE.С


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_canals.h"
#include        "energy.h"



uchar                   ibCan, ibGrp, ibDig;

uchar                   ibDay, ibMon;

uint                    iwHou;

ulong                   dwBuffC;

uint                    wBuffD;

real                    reBuffA, reBuffB;



void    ResetEngine(void)
{
uchar   i;

  for (i=0; i<bCANALS; i++)
  {
    mpreTransEng[i] = 1;
    mprePulseHou[i] = 500;

    mpreCount[i] = 0;
    mpreLosse[i] = 0;
  }

  for (i=0; i<bCANALS; i++)
  {
    mprePulseMnt[i] = mprePulseHou[i];
    mpreLevelDiv[i] = 1;

    mpreTransCnt[i] = 1;                      // в нормальном режиме: 1
  }
}



void    MakeLosse(void)
{
  reBuffA *= 1 + *PGetCanReal(mpreLosse,ibCan);
}


void    MakeValue(void)
{
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    reBuffA = *PGetCanReal(mpreTransEng,ibCan) / *PGetCanReal(mprePulseHou,ibCan);
    MakeLosse();
    SetCanReal(mpreValueEngHou,ibCan);

    reBuffA = *PGetCanReal(mpreTransCnt,ibCan) / *PGetCanReal(mprePulseHou,ibCan);
    MakeLosse();
    SetCanReal(mpreValueCntHou,ibCan);

    reBuffA = *PGetCanReal(mpreTransEng,ibCan) / *PGetCanReal(mprePulseMnt,ibCan);
    MakeLosse();
    SetCanReal(mpreValueEngMnt,ibCan);

    reBuffA = *PGetCanReal(mpreTransCnt,ibCan) / *PGetCanReal(mprePulseMnt,ibCan);
    MakeLosse();
    SetCanReal(mpreValueCntMnt,ibCan);
  }
}
