/*------------------------------------------------------------------------------
KEY_SET_PROFILES!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../console.h"
#include "../../access.h"
#include "../../realtime/realtime.h"
#include "../../realtime/realtime_spec.h"
#include "../../impulses/energy_spec.h"
#include "../../digitals/digitals.h"
#include "../../special/calc.h"



void    ShowDate_ClearCanals(uchar  ibDay);
void    ShowTime_ClearCanals(uchar  ibHhr);



//                                         0123456789ABCDEF
static char const       szSetProfiles[]  = "Редактирование  ",
                        szProcess[]      = "Обработка       ",
                        szMask[]         = " значение: _____",
                        szCanals[]       = "Каналы:         ",
                        szDateFrom[]     = "Дата от:        ",
                        szDateTo[]       = "Дата до:        ",
                        szTimeFrom[]     = "Время от:       ",
                        szTimeTo[]       = "Время до:       ",
                        szCanalFrom[]    = " от: __",
                        szCanalTo[]      = " до: __";



static void Show(void)
{
  Clear();
  ShowBool(enKeyboard != KBD_INPUT6);
}


void    SetProfiles(uchar  ibDigMin, uchar  ibDigMax, uint  wHhrMin, uint  wHhrMax, uint  wImp)
{
  ShowHi(szProcess); Clear();

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));

  memset(&mpflEngFrac, 0, sizeof(mpflEngFrac));
  memset(&mpflEngFracDigCan, 0, sizeof(mpflEngFracDigCan));

  uchar ibDig;
  for (ibDig=ibDigMin; ibDig<=ibDigMax; ibDig++)
  {
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);

      if (CompareCurrPrevLines(ibDig, c) == 1)
        mpboReadyCan[c] = true;
    }
  }


  fLoadHou = 0;

  bHhrInc = 0;

  uint iwHhr;
  for (iwHhr=0; iwHhr<wHOURS; iwHhr++)
  {
    if (fKey == true) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) ShowPercent((ulong)100*iwHhr/(wHOURS-1));
    if ((iwHhr % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHhr - bHhrInc) % wHOURS;


    if (iwDigHou == wHhrMax) fLoadHou = 1;

    if (fLoadHou == 1)
    {
      LoadImpHouSpec(iwDigHou,1);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if (mpboReadyCan[c] == true)
          mpwImpHouCanSpec[c] = wImp;
      }

      SaveImpHouSpec(1,iwDigHou);
    }

    if (iwDigHou == wHhrMin) fLoadHou = 0;
  }
}



void    key_SetProfiles1(void)
{
static uchar ibDigMin,ibDigMax,ibHhrMin,ibHhrMax,ibDayMin,ibDayMax;
static uint  wImp,wHhrMin,wHhrMax;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (SuperUser())
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szSetProfiles);
        Clear(); DelayInf();

        ShowHi(szCanals);
        strcpy(szLo+0,szCanalFrom);
      }
      else LongBeep();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibDigMin = GetCharLo(5,6) - 1;
      if (ibDigMin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibDigMax = GetCharLo(13,14) - 1;
      if ((ibDigMax < bCANALS) && (ibDigMax >= ibDigMin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szDateFrom); Clear();

        ibDayMin = 0;
        ShowDate_ClearCanals(ibDayMin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibHhrMin = 0;
      ShowTime_ClearCanals(ibHhrMin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      enKeyboard = KBD_INPUT4;
      ShowHi(szDateTo);
      Clear();

      ibDayMax = ibDayMin;
      ShowDate_ClearCanals(ibDayMax);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      enKeyboard = KBD_POSTINPUT4;
      ShowHi(szTimeTo);

      (ibDayMax == ibDayMin) ? (ibHhrMax = ibHhrMin) : (ibHhrMax = 0);
      ShowTime_ClearCanals(ibHhrMax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      wHhrMin = (GetDayHhrIndex(ibDayMin) + ibHhrMin) % wHOURS;
      wHhrMax = (GetDayHhrIndex(ibDayMax) + ibHhrMax) % wHOURS;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      wImp = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles(ibDigMin, ibDigMax, wHhrMin, wHhrMax, wImp);

      ShowHi(szSetProfiles);
      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_INPUT3)
    {
      if (++ibDayMin >= wHOURS/48) ibDayMin = 0;
      ShowDate_ClearCanals(ibDayMin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibHhrMin >= 48) ibHhrMin = 0;
      ShowTime_ClearCanals(ibHhrMin);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      (ibDayMax > 0) ? (ibDayMax--) : (ibDayMax = ibDayMin);
      ShowDate_ClearCanals(ibDayMax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      if (ibDayMax == ibDayMin)
      { if (++ibHhrMax >= 48) ibHhrMax = ibHhrMin; }
      else
      { if (++ibHhrMax >= 48) ibHhrMax = 0; }

      ShowTime_ClearCanals(ibHhrMax);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      sprintf(szLo+11,"65535");
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      ShiftLo(11,15);
    }
    else Beep();
  }
  else Beep();
}



void    key_SetProfiles2(void)
{
static uchar ibDigMin,ibDigMax,ibHhrMin,ibDayMin;
static uint  wImp,wHhrMin,wHhrMax;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (SuperUser())
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szSetProfiles);
        Clear(); DelayInf();

        ShowHi(szCanals);
        strcpy(szLo+0,szCanalFrom);
      }
      else LongBeep();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibDigMin = GetCharLo(5,6) - 1;
      if (ibDigMin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibDigMax = GetCharLo(13,14) - 1;
      if ((ibDigMax < bCANALS) && (ibDigMax >= ibDigMin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szDateFrom); Clear();

        ibDayMin = 0;
        ShowDate_ClearCanals(ibDayMin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibHhrMin = 0;
      ShowTime_ClearCanals(ibHhrMin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      wHhrMin = (GetDayHhrIndex(ibDayMin) + ibHhrMin) % wHOURS;
      wHhrMax = wHhrMin;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      wImp = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles(ibDigMin, ibDigMax, wHhrMin, wHhrMax, wImp);

      ShowHi(szSetProfiles);
      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_INPUT3)
    {
      if (++ibDayMin >= wHOURS/48) ibDayMin = 0;
      ShowDate_ClearCanals(ibDayMin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibHhrMin >= 48) ibHhrMin = 0;
      ShowTime_ClearCanals(ibHhrMin);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      sprintf(szLo+11,"65535");
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      ShiftLo(11,15);
    }
    else Beep();
  }
  else Beep();
}
