/*------------------------------------------------------------------------------
EXTENDED_4.C

 «начени€ счетчиков на конец мес€цев из буфера с дозапросом (oтчет є52 от 21.11.2009)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_6.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../sensors/device_f.h"
#include "../../sensors/automatic_p.h"
#include "../../sensors/automatic2.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4.h"



file const              flExt4Flag = {EXT_4_FLAG, &boExt4Flag, sizeof(boolean)};
file const              flExt4Months = {EXT_4_MONTHS, &bExt4Months, sizeof(uchar)};
file const              flExt4EnblCan = {EXT_4_ENBL_CAN, &mpboExt4EnblCan, sizeof(mpboExt4EnblCan)};


//                                         0123456789ABCDEF
static char const       szExtended4[]   = "ќпрос данных: 4 ",
                        szLinkOK[]      = "   ответ: есть  ",
                        szLinkError[]   = "   ответ: нет   ",
                        szDataOK[]      = "  данные: есть  ",
                        szDataError[]   = "  данные: нет   ",
                        szNone[]        = "*    пусто      ",
                        szBadDigital[]  = "*   ошибка !    ",
                        szBadFlash[]    = "* ошибка пам€ти ",
                        szModemLink[]   = "*    модем      ",
                        szDisabled[]    = "*  запрещено    ";



static uchar            bCount;



boolean SaveExt4Values(uchar  ibMon)
{
  return SaveBuff(EXT_4_MON_VALUES + ibMon*VALUE4_CAN_PAGES, &mpCntMonCan4, sizeof(mpCntMonCan4));
}


boolean LoadExt4Values(uchar  ibMon)
{
  return LoadBuff(EXT_4_MON_VALUES + ibMon*VALUE4_CAN_PAGES, &mpCntMonCan4, sizeof(mpCntMonCan4));
}



void    InitExtended4(void)
{
  LoadFileBoolean(&flExt4Flag, FALSE);
  LoadFileChar(&flExt4Months, 1, 12, 4);
  LoadFile(&flExt4EnblCan);
}


void    ResetExtended4(bool  fFull)
{ 
  boExt4Flag = FALSE;
  SaveFile(&flExt4Flag);

  bExt4Months = 4;
  SaveFile(&flExt4Months);


  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpboExt4EnblCan[c] = TRUE;
  }

  SaveFile(&flExt4EnblCan);


  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4Values(m);
  }


  cwDayCan4 = 0;
  cwMonCan4 = 0;
}



void    NextDayExtended4(void)
{ 
  cwDayCan4++;

  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));
  SaveExt4Values(ibHardMon);
}



void    NextMonExtended4(void) 
{
  cwMonCan4++;

  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));
  SaveExt4Values(ibHardMon);
}



static void MakeDevices(uchar  ibMon)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  if (ReadCntMonCan(ibMon, ibDig) == 0) 
  { 
    ShowLo(szLinkError); DelayInf();
  }
  else
  { 
    ShowLo(szLinkOK); DelayInf();

    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        value6 vl = mpCntMonCan4[c];

        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          vl.bSelf = ST4_OK;
          vl.reSelf = mpreChannelsB[diPrev.ibLine];
          ShowLo(szDataOK); DelayInf();
          if (c == ibDig) bCount++;
        }
        else
        {
          vl.bSelf = ST4_BADDIGITAL;
          vl.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        vl.tiUpdate = *GetCurrTimeDate();
        mpCntMonCan4[c] = vl;
      }
    }
  }
}


static void MakeDevice6(uchar  ibMon)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  if (ReadCntMonCanF_Buff(ibMon, ibDig) == 0) 
  { 
    ShowLo(szLinkError); DelayInf();
  }
  else
  { 
    ShowLo(szLinkOK); DelayInf();

    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
      	value6 vl = mpCntMonCan4[c];

        InitPop(15 + 15*c);
        status st = (status) PopChar();
        PopChar(); PopChar(); PopChar(); PopChar();
        real re = PopFloat();

        if (st == ST4_OK)
        {
          vl.bSelf = st;
          vl.reSelf = re;
          ShowLo(szDataOK); DelayInf();
          if (c == ibDig) bCount++;
        }
        else
        {
          vl.bSelf = st;
          vl.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        vl.tiUpdate = *GetCurrTimeDate();
        mpCntMonCan4[c] = vl;
      }
    }
  }
}


void    MakeExtended4(void)
{
  if ((boExt4Flag == TRUE) && (mpboExt4EnblCan[ibDig] == TRUE))
  {
    ShowHi(szExtended4); 
    Clear(); sprintf(szLo+3,"глубина: %u", bExt4Months);
    DelayInf();

    bCount = 0;

    uchar m;
    for (m=0; m<bExt4Months; m++)
    {
      if (fKey == true) break;

      uchar ibMon = (bMONTHS + ibHardMon - m) % bMONTHS;
      LoadExt4Values(ibMon);

      value6 vl = mpCntMonCan4[ibDig];
      if (vl.bSelf == ST4_OK) continue;

      Clear(); sprintf(szLo+3,"мес€ц: %-2u",ibMon+1); DelayInf();

      (GetDigitalDevice(ibDig) != 6) ? MakeDevices(ibMon) : MakeDevice6(ibMon);

      SaveExt4Values(ibMon);
    }

    Clear(); sprintf(szLo+3,"прин€то: %u", bCount); DelayInf();

    ShowCanalNumber(ibDig);
    Clear();
  }
}
