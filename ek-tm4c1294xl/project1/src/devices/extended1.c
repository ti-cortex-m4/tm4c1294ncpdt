/*------------------------------------------------------------------------------
EXTENDED1.Ñ


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended1.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../hardware/watchdog.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../sensors/automatic2.h"
#include        "../time/timedate.h"
#include        "../time/rtc.h"
#include        "../engine.h"
#include        "../energy.h"
#include        "extended1.h"



void    InitExtended1(void)
{
}


void    ResetExtended1(void)
{
}



void    MakeExtended1(void)
{
  if (boDisableEsc1 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscU[ibDig] == FALSE)
  {
    ShowHi(szDirectEscU); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadTimeCan(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_U_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_U_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          moAlt.tiAlfa = tiChannelC;
          mpcwEscU_OK[c]++;

          moAlt.tiBeta = *GetCurrTimeDate();
          mpmoEsc_U[c] = moAlt;

          mpboDefEscU[c] = TRUE;
          //AddDigRecord(EVE_ESC_U_DATA);
        }
        else
        {
          moAlt.tiAlfa = tiZero;
          mpcwEscU_Error[c]++;
        }
      }
    }
  }

  if (boDisableEsc2 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscV[ibDig] == FALSE)
  {
    ShowHi(szDirectEscV); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntMonCan(tiCurr.bMonth-1, ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_V_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_V_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          reBuffA = GetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscV_OK[c]++;

          mpreEsc_V[c] = reBuffA;
          mptiEsc_V[c] = *GetCurrTimeDate();

          mpboDefEscV[c] = TRUE;
          //AddDigRecord(EVE_ESC_V_DATA);
        }
        else
        {
          reBuffA = 0;
          mpcwEscV_Error[c]++;
        }
      }
    }
  }

  if (boDisableEsc3 == TRUE) {
    BlockProgram2(wSET_DISABLE_ESC, 0); DelayInf();
  }
  else if (mpboDefEscS[ibDig] == FALSE)
  {
    ShowHi(szDirectEscS); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntCurrCan(ibDig) == 1) { OK(); /*AddDigRecord(EVE_ESC_S_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_S_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          ResetWDT();
          reBuffA = GetCanReal(mpreChannelsB, diPrev.ibLine);
          mpcwEscS_OK[c]++;

          mpreEsc_S[c] = reBuffA;
          mptiEsc_S[c] = *GetCurrTimeDate();

//          MakeExtended6(ibCan);
//          MakeExtended7(ibCan);
//          MakeDiagram(ibCan);

          mpboDefEscS[c] = TRUE;
          //AddDigRecord(EVE_ESC_S_DATA);
        }
        else
        {
          reBuffA = 0;
          mpcwEscS_Error[c]++;
        }
      }
    }
  }

  ShowCanalNumber(ibDig);
  Clear();
}

