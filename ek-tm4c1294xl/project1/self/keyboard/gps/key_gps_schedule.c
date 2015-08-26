/*------------------------------------------------------------------------------
KEY_GPS_SCHEDULE,С

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "     График     ",
                        szMessage2[]    = "коррекции по GPS";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



static void Show(uchar  ibHhr)
{
  Clear();
  sprintf(szLo+1,"%02u:%02u",ibHhr/2,(ibHhr%2)*30);

  if (mpboScheduleGps[ibHhr] == false)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';

  sprintf(szLo+14,"%2u",ibHhr+1);
}



void    key_SetGpsSchedule(void)
{
static uchar ibHhr;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (UseGps())
      {
        enKeyboard = KBD_INPUT1;
        LoadSlide(pszMessages);

        HalfHour();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibHhr = 0;
      Show(ibHhr);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibHhr = GetCharLo(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        Show(ibHhr);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibHhr >= 48) ibHhr = 0;
      Show(ibHhr);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      mpboScheduleGps[ibHhr] = InvertBoolean(mpboScheduleGps[ibHhr]);
      SaveCache(&chScheduleGps);

      Show(ibHhr);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      (ibHhr > 0) ? (ibHhr--) : (ibHhr = 48-1);
      Show(ibHhr);
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}
