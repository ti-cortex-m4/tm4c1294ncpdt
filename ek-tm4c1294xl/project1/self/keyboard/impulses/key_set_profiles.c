/*------------------------------------------------------------------------------
KEY_SET_PROFILES.C


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
                        szProfilesMask[] = " значение: _____",
                        szProcess[]      = "Обработка       ",
                        szCanalsTitle[]  = "Каналы:         ",
                        szDateFrom[]     = "Дата от:        ",
                        szDateTo[]       = "Дата до:        ",
                        szTimeFrom[]     = "Время от:       ",
                        szTimeTo[]       = "Время до:       ",
                        szCanalFrom[]    = " от: __",
                        szCanalTo[]      = " до: __";



static void ShowAnswer(void)
{
  Clear();
  ShowBool(enKeyboard != KBD_INPUT6);
}


void    SetProfiles(uchar  ibDigMin, uchar  ibDigMax, uint  iwAmin, uint  iwAmax, uint  wImp)
{
  ShowHi(szProcess); Clear();

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));

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

  bHouInc = 0;

  uint iwHhr;
  for (iwHhr=0; iwHhr<wHOURS; iwHhr++) 
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) ShowPercent((ulong)100*iwHhr/(wHOURS-1));    
    if ((iwHhr % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHhr - bHouInc) % wHOURS;


    if (iwDigHou == iwAmax) fLoadHou = 1;

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

    if (iwDigHou == iwAmin) fLoadHou = 0;
  }
}



void    key_SetProfiles1(void)
{ 
static uchar ibDigMin,ibDigMax,ibYmin,ibYmax,ibZmin,ibZmax;
static uint  wImp, iwAmin,iwAmax;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (SuperUser())
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szSetProfiles);
        Clear(); DelayInf();

        ShowHi(szCanalsTitle);
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

        ibZmin = 0;
        ShowDate_ClearCanals(ibZmin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibYmin = 0;
      ShowTime_ClearCanals(ibYmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      enKeyboard = KBD_INPUT4;
      ShowHi(szDateTo);
      Clear();

      ibZmax = ibZmin;
      ShowDate_ClearCanals(ibZmax);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      enKeyboard = KBD_POSTINPUT4;
      ShowHi(szTimeTo);

      (ibZmax == ibZmin) ? (ibYmax = ibYmin) : (ibYmax = 0);
      ShowTime_ClearCanals(ibYmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      iwAmin = (GetDayHhrIndex(ibZmin) + ibYmin) % wHOURS;
      iwAmax = (GetDayHhrIndex(ibZmax) + ibYmax) % wHOURS;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szProfilesMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      wImp = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      ShowAnswer();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles(ibDigMin, ibDigMax, iwAmin, iwAmax, wImp);

      ShowHi(szSetProfiles);
      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_INPUT3)
    {
      if (++ibZmin >= wHOURS/48) ibZmin = 0;
      ShowDate_ClearCanals(ibZmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibYmin >= 48) ibYmin = 0;
      ShowTime_ClearCanals(ibYmin);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      (ibZmax > 0) ? (ibZmax--) : (ibZmax = ibZmin);
      ShowDate_ClearCanals(ibZmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      if (ibZmax == ibZmin)
      { if (++ibYmax >= 48) ibYmax = ibYmin; }
      else
      { if (++ibYmax >= 48) ibYmax = 0; }
      
      ShowTime_ClearCanals(ibYmax);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {           
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      ShowAnswer(); 
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
static uchar ibDigMin,ibDigMax,ibYmin,ibZmin;
static uint  wImp,iwAmin,iwAmax;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (SuperUser())
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szSetProfiles);
        Clear(); DelayInf();

        ShowHi(szCanalsTitle);
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

        ibZmin = 0;
        ShowDate_ClearCanals(ibZmin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibYmin = 0;
      ShowTime_ClearCanals(ibYmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      iwAmin = (GetDayHhrIndex(ibZmin) + ibYmin) % wHOURS;
      iwAmax = iwAmin;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szProfilesMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      wImp = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      ShowAnswer();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles(ibDigMin, ibDigMax, iwAmin, iwAmax, wImp);

      ShowHi(szSetProfiles);
      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_INPUT3)
    {
      if (++ibZmin >= wHOURS/48) ibZmin = 0;
      ShowDate_ClearCanals(ibZmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibYmin >= 48) ibYmin = 0;
      ShowTime_ClearCanals(ibYmin);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {           
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      ShowAnswer(); 
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
