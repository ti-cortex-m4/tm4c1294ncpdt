/*------------------------------------------------------------------------------
EXTENDED_1.Ñ


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_extended_1.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../digitals/extended/extended_6.h"
#include "../../digitals/extended/extended_7.h"
#include "../../sensors/automatic2.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../engine.h"
#include "../../energy.h"
#include "extended_1.h"



cache const             chEscS_Value = {ESC_S_VALUE, &mpdbEsc_S, sizeof(mpdbEsc_S)};
cache const             chEscS_Time = {ESC_S_TIME, &mptiEsc_S, sizeof(mptiEsc_S)};

cache const             chEscV_Value = {ESC_V_VALUE, &mpdbEsc_V, sizeof(mpdbEsc_V)};
cache const             chEscV_Time = {ESC_V_TIME, &mptiEsc_V, sizeof(mptiEsc_V)};

cache const             chEscU_Value = {ESC_U_VALUE, &mptiEsc_U1, sizeof(mptiEsc_U1)};
cache const             chEscU_Time = {ESC_U_TIME, &mptiEsc_U2, sizeof(mptiEsc_U2)};

cache const             chDsblEscU = {DSBL_ESC_U, &boDsblEscU, sizeof(bool)};
cache const             chDsblEscV = {DSBL_ESC_V, &boDsblEscV, sizeof(bool)};
cache const             chDsblEscS = {DSBL_ESC_S, &boDsblEscS, sizeof(bool)};

cache const             chMntEscS = {MNT_ESC_S, &boMntEscS, sizeof(bool)};

cache const             chExtendedEscU = {EXTENDED_ESC_U, &boExtendedEscU, sizeof(bool)};
cache const             chExtendedEscV = {EXTENDED_ESC_V, &boExtendedEscV, sizeof(bool)};
cache const             chExtendedEscS = {EXTENDED_ESC_S, &boExtendedEscS, sizeof(bool)};



void    InitExtended1(void)
{
  LoadCache(&chEscS_Value);
  LoadCache(&chEscS_Time);

  LoadCache(&chEscV_Value);
  LoadCache(&chEscV_Time);

  LoadCache(&chEscU_Value);
  LoadCache(&chEscU_Time);

  LoadCache(&chDsblEscU);
  LoadCache(&chDsblEscV);
  LoadCache(&chDsblEscS);

  LoadCache(&chMntEscS);

  LoadCache(&chExtendedEscU);
  LoadCache(&chExtendedEscV);
  LoadCache(&chExtendedEscS);
}


void    ResetExtended1(void)
{
  memset(&mpdbEsc_S, 0, sizeof(mpdbEsc_S));
  SaveCache(&chEscS_Value);

  memset(&mptiEsc_S, 0, sizeof(mptiEsc_S));
  SaveCache(&chEscS_Time);


  memset(&mpdbEsc_V, 0, sizeof(mpdbEsc_V));
  SaveCache(&chEscV_Value);

  memset(&mptiEsc_V, 0, sizeof(mptiEsc_V));
  SaveCache(&chEscV_Time);


  memset(&mptiEsc_U1, 0, sizeof(mptiEsc_U1));
  SaveCache(&chEscU_Value);

  memset(&mptiEsc_U2, 0, sizeof(mptiEsc_U2));
  SaveCache(&chEscU_Time);


  boDsblEscU = false;
  SaveCache(&chDsblEscU);

  boDsblEscV = false;
  SaveCache(&chDsblEscV);

  boDsblEscS = false;
  SaveCache(&chDsblEscS);


  boMntEscS = false;
  SaveCache(&chMntEscS);


  boExtendedEscU = true;
  SaveCache(&chExtendedEscU);

  boExtendedEscV = true;
  SaveCache(&chExtendedEscV);

  boExtendedEscS = true;
  SaveCache(&chExtendedEscS);
}



void    MakeExtended1(void)
{
  if (boDsblEscU == true)
  {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else
  {
    ShowHi(szDirectEscU); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    time2 ti2 = ReadTimeCan(ibDig);
    if (ti2.fValid) { OK(); /*AddDigRecord(EVE_ESC_U_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_U_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == true)
      {
        if (mpboChannelsA[diPrev.ibLine] == true)
        {
          mptiEsc_U1[c] = tiChannelC;
          mptiEsc_U2[c] = *GetCurrTimeDate();

          mpcwEscU_OK[c]++;
          /*AddDigRecord(EVE_ESC_U_DATA);*/
        }
        else
        {
          mpcwEscU_Error[c]++;
        }
      }
    }

    SaveCache(&chEscU_Value);
    SaveCache(&chEscU_Time);
  }

  if (boDsblEscV == true)
  {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else
  {
    ShowHi(szDirectEscV); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    double2 db2 = ReadCntMonCan(tiCurr.bMonth-1, ibDig);
    if (db2.fValid) { OK(); /*AddDigRecord(EVE_ESC_V_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_V_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == true)
      {
        if (mpboChannelsA[diPrev.ibLine] == true)
        {
          double db = mpdbChannelsC[diPrev.ibLine];

          mpdbEsc_V[c] = db;
          mptiEsc_V[c] = *GetCurrTimeDate();

          mpcwEscV_OK[c]++;
          /*AddDigRecord(EVE_ESC_V_DATA);*/
        }
        else
        {
          mpcwEscV_Error[c]++;
        }
      }
    }

    SaveCache(&chEscV_Value);
    SaveCache(&chEscV_Time);
  }

  if (boDsblEscS == true)
  {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else
  {
    ShowHi(szDirectEscS); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    double2 db2 = ReadCntCurrCan(ibDig);
    if (db2.fValid) { OK(); /*AddDigRecord(EVE_ESC_S_OK);*/ } else { Error(); /*AddDigRecord(EVE_ESC_S_ERROR);*/ }

    LoadCurrDigital(ibDig);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == true)
      {
        if (mpboChannelsA[diPrev.ibLine] == true)
        {
          double db = mpdbChannelsC[diPrev.ibLine];

          mpdbEsc_S[c] = db;
          mptiEsc_S[c] = *GetCurrTimeDate();

          MakeExtended6(c, db);
          MakeExtended7(c, db);
          //MakeDiagram(c);

          mpcwEscS_OK[c]++;
          /*AddDigRecord(EVE_ESC_S_DATA);*/
        }
        else
        {
          mpcwEscS_Error[c]++;
        }
      }
    }

    SaveCache(&chEscS_Value);
    SaveCache(&chEscS_Time);
  }

  ShowCanalNumber(ibDig);
  Clear();
}
