/*------------------------------------------------------------------------------
EXTENDED_1.Ñ


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended_1.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../hardware/watchdog.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../devices/extended_7.h"
#include        "../sensors/automatic2.h"
#include        "../time/timedate.h"
#include        "../time/rtc.h"
#include        "../engine.h"
#include        "../energy.h"
#include        "../flash/files.h"
#include        "extended_1.h"



file const              flDsblEscU = {FLS_DSBL_ESC_U, &boDsblEscU, sizeof(boolean)};
file const              flDsblEscV = {FLS_DSBL_ESC_V, &boDsblEscV, sizeof(boolean)};
file const              flDsblEscS = {FLS_DSBL_ESC_S, &boDsblEscS, sizeof(boolean)};

file const              flMntEscS = {FLS_MNT_ESC_S, &boMntEscS, sizeof(boolean)};

file const              flExtendedEscU = {FLS_EXTENDED_ESC_U, &boExtendedEscU, sizeof(boolean)};
file const              flExtendedEscV = {FLS_EXTENDED_ESC_V, &boExtendedEscV, sizeof(boolean)};
file const              flExtendedEscS = {FLS_EXTENDED_ESC_S, &boExtendedEscS, sizeof(boolean)};



void    InitExtended1(void)
{
  memset(&mpreEsc_S, 0, sizeof(mpreEsc_S));
  memset(&mptiEsc_S, 0, sizeof(mptiEsc_S));

  memset(&mpreEsc_V, 0, sizeof(mpreEsc_V));
  memset(&mptiEsc_V, 0, sizeof(mptiEsc_V));

  memset(&mptiEsc_U1, 0, sizeof(mptiEsc_U1));
  memset(&mptiEsc_U2, 0, sizeof(mptiEsc_U2));

  LoadFile(&flDsblEscU);
  LoadFile(&flDsblEscV);
  LoadFile(&flDsblEscS);

  LoadFile(&flMntEscS);

  LoadFile(&flExtendedEscU);
  LoadFile(&flExtendedEscV);
  LoadFile(&flExtendedEscS);
}


void    ResetExtended1(void)
{
  boDsblEscU = FALSE;
  SaveFile(&flDsblEscU);

  boDsblEscV = FALSE;
  SaveFile(&flDsblEscV);

  boDsblEscS = FALSE;
  SaveFile(&flDsblEscS);


  boMntEscS = FALSE;
  SaveFile(&flMntEscS);


  boExtendedEscU = TRUE;
  SaveFile(&flExtendedEscU);

  boExtendedEscV = TRUE;
  SaveFile(&flExtendedEscV);

  boExtendedEscS = TRUE;
  SaveFile(&flExtendedEscS);
}



void    MakeExtended1(void)
{
  if (boDsblEscU == TRUE) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
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
          mptiEsc_U1[c] = tiChannelC;
          mpcwEscU_OK[c]++;

          mptiEsc_U2[c] = *GetCurrTimeDate();

          mpboDefEscU[c] = TRUE;
          //AddDigRecord(EVE_ESC_U_DATA);
        }
        else
        {
          tiChannelC = tiZero;
          mpcwEscU_Error[c]++;
        }
      }
    }
  }

  if (boDsblEscV == TRUE) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
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

  if (boDsblEscS == TRUE) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
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

//          MakeExtended6(c);
          MakeExtended7(c, reBuffA);
//          MakeDiagram(c);

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

