/*------------------------------------------------------------------------------
EXTENDED1.С


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_extended1.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../digitals/digitals.h"
#include        "../sensors/automatic2.h"
#include        "../energy.h"



void    InitExtended1(void)
{
}


void    ResetExtended1(void)
{
}


void    MakeExtended1(void)
{
uchar   ibCan;

//  AddDigRecord(EVE_EXTENDED);

  // расширенный опрос информации для Esc U
  if (boDisableEsc1 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscU[ibDig] == FALSE)
  {
    ShowHi(szDirectEscU); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadTimeDate(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_U_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_U_ERROR);*/ }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines(ibDig, ibCan) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          moAlt.tiAlfa = tiChannelC;
          mpcwEscU_OK[ibCan]++;

          moAlt.tiBeta = *GetCurrTimeDate();
          SetCanMoment(&mpmoEsc_U, ibCan);

          mpboDefEscU[ibCan] = TRUE;
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
  if (boDisableEsc2 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscV[ibDig] == FALSE)
  {
    ShowHi(szDirectEscV); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntMonCan(tiCurr.bMonth-1, ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_V_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_V_ERROR);*/ }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines(ibDig, ibCan) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          reBuffA = *PGetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscV_OK[ibCan]++;

          SetCanReal(&mpreEsc_V, ibCan);
          tiAlt = *GetCurrTimeDate();
          SetCanTime(mptiEsc_V, ibCan);

          mpboDefEscV[ibCan] = TRUE;
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
  if (boDisableEsc3 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscS[ibDig] == FALSE)
  {
    ShowHi(szDirectEscS); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadSensors(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_S_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_S_ERROR);*/ }

    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines(ibDig, ibCan) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          ResetWDT();
          reBuffA = *PGetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscS_OK[ibCan]++;

          SetCanReal(&mpreEsc_S, ibCan);
          tiAlt = *GetCurrTimeDate();
          SetCanTime(mptiEsc_S, ibCan);

          MakeExtended6(ibCan);
          MakeExtended7(ibCan);
          MakeDiagram(ibCan);

          mpboDefEscS[ibCan] = TRUE;
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

