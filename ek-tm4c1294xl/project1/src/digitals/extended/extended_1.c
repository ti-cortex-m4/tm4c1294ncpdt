/*------------------------------------------------------------------------------
EXTENDED_1.Ñ


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../hardware/watchdog.h"
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
#include "../../flash/files.h"
#include "extended_1.h"



file const              flDsblEscU = {DSBL_ESC_U, &boDsblEscU, sizeof(bool)};
file const              flDsblEscV = {DSBL_ESC_V, &boDsblEscV, sizeof(bool)};
file const              flDsblEscS = {DSBL_ESC_S, &boDsblEscS, sizeof(bool)};

file const              flMntEscS = {MNT_ESC_S, &boMntEscS, sizeof(bool)};

file const              flExtendedEscU = {EXTENDED_ESC_U, &boExtendedEscU, sizeof(bool)};
file const              flExtendedEscV = {EXTENDED_ESC_V, &boExtendedEscV, sizeof(bool)};
file const              flExtendedEscS = {EXTENDED_ESC_S, &boExtendedEscS, sizeof(bool)};



void    InitExtended1(void)
{
  memset(&mpdbEsc_S, 0, sizeof(mpdbEsc_S));
  memset(&mptiEsc_S, 0, sizeof(mptiEsc_S));

  memset(&mpdbEsc_V, 0, sizeof(mpdbEsc_V));
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
  boDsblEscU = false;
  SaveFile(&flDsblEscU);

  boDsblEscV = false;
  SaveFile(&flDsblEscV);

  boDsblEscS = false;
  SaveFile(&flDsblEscS);


  boMntEscS = false;
  SaveFile(&flMntEscS);


  boExtendedEscU = true;
  SaveFile(&flExtendedEscU);

  boExtendedEscV = true;
  SaveFile(&flExtendedEscV);

  boExtendedEscS = true;
  SaveFile(&flExtendedEscS);
}



void    MakeExtended1(void)
{
  if (boDsblEscU == true) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else if (mpboDefEscU[ibDig] == false)
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
          mpcwEscU_OK[c]++;

          mptiEsc_U2[c] = *GetCurrTimeDate();

          mpboDefEscU[c] = true;
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

  if (boDsblEscV == true) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else if (mpboDefEscV[ibDig] == false)
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
          mpcwEscV_OK[c]++;

          mpdbEsc_V[c] = db;
          mptiEsc_V[c] = *GetCurrTimeDate();

          mpboDefEscV[c] = true;
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

  if (boDsblEscS == true) {
    BlockProgram2(wSET_DSBL_ESC, 0); DelayInf();
  }
  else if (mpboDefEscS[ibDig] == false)
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
          ResetWDT();
          double db = mpdbChannelsC[diPrev.ibLine];
          mpcwEscS_OK[c]++;

          mpdbEsc_S[c] = db;
          mptiEsc_S[c] = *GetCurrTimeDate();

          MakeExtended6(c, db);
          MakeExtended7(c, db);
//          MakeDiagram(c);

          mpboDefEscS[c] = true;
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

