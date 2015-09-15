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



void    ShowDateClear(uchar  j);
void    ShowTimeClear(uchar  j);



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



static uchar            ibXmin, ibXmax, ibYmin, ibYmax, ibZmin, ibZmax;
static uint             iwA, iwAmin, iwAmax;



static void ShowAnswerProfiles(void)
{
  Clear();
  ShowBool(enKeyboard != KBD_INPUT6);
}


void    SetProfiles(void)
{
  ShowHi(szProcess); Clear();

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));

  uint wBuffD = ((wHOURS + iwHardHou - iwAmin) % wHOURS) + 4;

  uchar ibDig;
  for (ibDig=ibXmin; ibDig<=ibXmax; ibDig++)
  { 
    LoadCurrDigital(ibDig);

    uchar ibCan;
    for (ibCan=0; ibCan<bCANALS; ibCan++) 
    {
      LoadPrevDigital(ibCan);

      if (CompareCurrPrevLines(ibDig, ibCan) == 1)
        mpboReadyCan[ibCan] = true;
    } 
  }


  fLoadHou = 0;

  bHouInc = 0;

  uint iwHou;
  for (iwHou=0; iwHou<wHOURS; iwHou++) 
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHou % 0x10) == 0) ShowPercent((ulong)100*iwHou/(wHOURS-1));    
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;


    if (iwDigHou == iwAmax) fLoadHou = 1;

    if (fLoadHou == 1)
    {
      LoadImpHouSpec(iwDigHou,1);                   // обработка по получасам
    
      uchar ibCan;
      for (ibCan=0; ibCan<bCANALS; ibCan++)         // обработка по каналам                
      {
        if (mpboReadyCan[ibCan] == true)
          mpwImpHouCanSpec[ibCan] = iwA;
      }

      SaveImpHouSpec(1,iwDigHou);
    }

    if (iwDigHou == iwAmin) fLoadHou = 0;
  }
}



void    key_SetProfiles1(void)
{ 
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
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szDateFrom); Clear();

        ibZmin = 0;
        ShowDateClear(ibZmin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      enKeyboard = KBD_INPUT4;
      ShowHi(szDateTo);
      Clear();

      ibZmax = ibZmin;
      ShowDateClear(ibZmax);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      enKeyboard = KBD_POSTINPUT4;
      ShowHi(szTimeTo);

      (ibZmax == ibZmin) ? (ibYmax = ibYmin) : (ibYmax = 0);
      ShowTimeClear(ibYmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      iwAmin = (GetDayHouIndex(ibZmin) + ibYmin) % wHOURS;
      iwAmax = (GetDayHouIndex(ibZmax) + ibYmax) % wHOURS;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szProfilesMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      iwA = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      ShowAnswerProfiles();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles();

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
      ShowDateClear(ibZmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibYmin >= 48) ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      (ibZmax > 0) ? (ibZmax--) : (ibZmax = ibZmin);
      ShowDateClear(ibZmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      if (ibZmax == ibZmin)
      { if (++ibYmax >= 48) ibYmax = ibYmin; }
      else
      { if (++ibYmax >= 48) ibYmax = 0; }
      
      ShowTimeClear(ibYmax);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {           
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      ShowAnswerProfiles(); 
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
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szDateFrom); Clear();

        ibZmin = 0;
        ShowDateClear(ibZmin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      iwAmin = (GetDayHouIndex(ibZmin) + ibYmin) % wHOURS;
      iwAmax = iwAmin;

      enKeyboard = KBD_INPUT5;
      ShowHi(szSetProfiles);
      ShowLo(szProfilesMask);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      iwA = GetIntLo(11,15);

      enKeyboard = KBD_INPUT6;
      ShowAnswerProfiles();
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      SetProfiles();

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
      ShowDateClear(ibZmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibYmin >= 48) ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {           
      (enKeyboard == KBD_INPUT6) ? (enKeyboard = KBD_POSTINPUT6) : (enKeyboard = KBD_INPUT6);
      ShowAnswerProfiles(); 
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
