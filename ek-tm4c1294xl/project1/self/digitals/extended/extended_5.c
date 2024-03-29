/*------------------------------------------------------------------------------
EXTENDED_5!C

 �������� ���������
 �� ������ ������� �����
 �� ������ � ���������� �� ������� ('����� �18a �� 01.02.2008')
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_profile.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_display.h"
#include "../../devices/devices.h"
#include "../../time/rtc.h"
#include "../../console.h"
#include "automatic_5.h"
#include "extended_5.h"



cache const             chExt5Flag = {EXT_5_FLAG, &fExt5Flag, sizeof(bool)};
file const              flExt5Values = {EXT_5_VALUES, &mpCntDayCan5, sizeof(mpCntDayCan5)};


//                                         0123456789ABCDEF
static char const       szExtended5[]   = "����� ������: 5 ";



static value5a          stBuff[4];



void    InitExtended5(void)
{
  LoadCache(&chExt5Flag);
  LoadFile(&flExt5Values);
}


void    ResetExtended5(bool  fFull)
{
  if (fFull)
  {
    fExt5Flag = false;
    SaveCache(&chExt5Flag);
  }

  memset(&mpCntDayCan5, 0, sizeof(mpCntDayCan5));
  SaveFile(&flExt5Values);
}



void    NextDayExtended5(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpCntDayCan5[c].boSuccess = false;
  }

  SaveFile(&flExt5Values);
}



static bool MakeDevices(void)
{
  memset(&stBuff, 0, sizeof(stBuff));

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    sprintf(szLo+14,"T%u",t+1); DelayInf();

    if (fKey == true) return false;
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntDayTariff(ibDig,t+1) == 0) return false;

    uchar i;
    for (i=0; i<4; i++)
    {
      stBuff[i].mpdbValuesT[t] = mpdbChannelsC[i];
    }
  }

  return true;
}


void    MakeExtended5(void)
{
  if ((fExt5Flag == true) && ((mpCntDayCan5[ibDig].boSuccess == false) || (boManualProfile == true)))
  {
    ShowHi(szExtended5); Clear();

    if (MakeDevices() == true)
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == true)
        {
          mpCntDayCan5[c].cwSuccess++;
          mpCntDayCan5[c].tiUpdate = *GetCurrTimeDate();
          mpCntDayCan5[c].stValue = stBuff[diPrev.ibLine];
          mpCntDayCan5[c].boSuccess = true;
        }
      }
    }
    else
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == true)
        {
          mpCntDayCan5[c].cwError++;
        }
      }

      Error(); DelayInf();
    }

    SaveFile(&flExt5Values);

    ShowCanalNumber(ibDig);
    Clear();
  }
}
