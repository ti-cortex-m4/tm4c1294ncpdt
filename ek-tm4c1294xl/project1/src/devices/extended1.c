/*------------------------------------------------------------------------------
EXTENDED1.С


------------------------------------------------------------------------------*/

#include        "../main.h"



/*
void    MakeExtended1(void)
{
//  AddDigRecord(EVE_EXTENDED);

  // расширенный опрос информации для Esc U
  if (boDisableEsc1 == boTrue) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscU[ibDig] == boFalse)
  {
    ShowHi(szDirectEscU); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadTimeDate(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_U_OK);* / } else { Error(); /*AddDigRecord(EVE_ESC_U_ERROR);* / }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == boTrue)
        {
          moAlt.tiAlfa = tiChannelC;
          mpcwEscU_OK[ibCan]++;

          moAlt.tiBeta = *PGetCurrTimeDate();
          SetCanMoment(&mpmoEsc_U, ibCan);

          mpboDefEscU[ibCan] = boTrue;
          //AddDigRecord(EVE_ESC_U_DATA);
        }
        else
        {
          moAlt.tiAlfa = tiZero;
          mpcwEscU_Error[ibCan]++;
        }
      }
    }
  }

  // расширенный опрос информации для Esc V (только за текущий месяц)
  if (boDisableEsc2 == boTrue) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscV[ibDig] == boFalse)
  {
    ShowHi(szDirectEscV); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntMonCan(tiCurr.bMonth-1, ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_V_OK);* / } else { Error(); /*AddDigRecord(EVE_ESC_V_ERROR);* / }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == boTrue)
        {
          reBuffA = *PGetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscV_OK[ibCan]++;

          SetCanReal(&mpreEsc_V, ibCan);
          tiAlt = *PGetCurrTimeDate();
          SetCanTime(mptiEsc_V, ibCan);

          mpboDefEscV[ibCan] = boTrue;
          //AddDigRecord(EVE_ESC_V_DATA);
        }
        else
        {
          reBuffA = 0;
          mpcwEscV_Error[ibCan]++;
        }
      }
    }
  }

  // расширенный опрос информации для Esc S
  if (boDisableEsc3 == boTrue) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscS[ibDig] == boFalse)
  {
    ShowHi(szDirectEscS); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadSensors(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_S_OK);* / } else { Error(); /*AddDigRecord(EVE_ESC_S_ERROR);* / }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == boTrue)
        {
          ResetWDT();
          reBuffA = *PGetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscS_OK[ibCan]++;

          SetCanReal(&mpreEsc_S, ibCan);
          tiAlt = *PGetCurrTimeDate();
          SetCanTime(mptiEsc_S, ibCan);

          MakeExtended6(ibCan);
          MakeExtended7(ibCan);
          MakeDiagram(ibCan);

          mpboDefEscS[ibCan] = boTrue;
          //AddDigRecord(EVE_ESC_S_DATA);
        }
        else
        {
          reBuffA = 0;
          mpcwEscS_Error[ibCan]++;
        }
      }
    }
  }

  ShowDigitalHi(); Clear();
}
*/
