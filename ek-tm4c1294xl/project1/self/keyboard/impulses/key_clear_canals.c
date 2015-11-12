/*------------------------------------------------------------------------------
_CLEAR!C


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
#include "../../special/recalc.h"
#include "../../time/calendar.h"



//                                         0123456789ABCDEF
static char const       szClearCanals[]   = "Очистка каналов ",
                        szCanals[]        = "Каналы:         ",
                        szDateFrom[]      = "Дата от:        ",
                        szDateTo[]        = "Дата до:        ",
                        szTimeFrom[]      = "Время от:       ",
                        szTimeTo[]        = "Время до:       ",
                        szCanalFrom[]     = " от: __",
                        szCanalTo[]       = " до: __";



void    ShowDate_ClearCanals(uchar  ibDay)
{
  ulong dw = DateToHouIndex(tiCurr);
  dw -= (uint)48*ibDay + GetCurrHouIndex();
  time ti = HouIndexToDate(dw);

  sprintf(szLo+7,"%02u.%02u.%02u",ti.bDay,ti.bMonth,ti.bYear);
  sprintf(szHi+13,".%02u",ibDay);
}


void    ShowTime_ClearCanals(uchar  ibHhr)
{
  sprintf(szLo+1,"%02u:%02u",ibHhr/2,(ibHhr%2)*30);
  sprintf(szHi+13,".%02u",ibHhr);
}



static void Show(void)
{
  Clear();
  ShowBool(enKeyboard != KBD_INPUT5);
}


void    key_ClearCanals(void)
{
static uchar ibDigMin,ibDigMax,ibHhrMin,ibHhrMax,ibDayMin,ibDayMax;
static uint  wHhrMin,wHhrMax;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (SuperUser())
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szClearCanals);
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

      ShowHi(szClearCanals);
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      (ClearCanals(ibDigMin, ibDigMax, wHhrMin, wHhrMax, true) == true) ? OK() : Error();

      ShowHi(szClearCanals);
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
    else if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      (enKeyboard == KBD_INPUT5) ? (enKeyboard = KBD_POSTINPUT5) : (enKeyboard = KBD_INPUT5);
      Show();
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
    else Beep();
  }
  else Beep();
}

