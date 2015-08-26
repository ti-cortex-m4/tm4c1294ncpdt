/*------------------------------------------------------------------------------
KEY_GPS_CORRECT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"
#include "../../time/rtc.h"
#include "../../time/timedate_display.h"
#include "../../flash/records.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   Коррекция    ",
                        szMessage2[]    = " времени по GPS ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



static void Show(void)
{
  time2 ti2 = ReadTimeDateGps();
  if (ti2.fValid == false)
  {
    Error(); DelayInf(); Clear();
  }
  else
  {
    if (ShowStatusGps() == 1)
    {
      ShowDeltaTime(ti2.tiValue);
    }
  }
}


void    key_GetGpsCorrect(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UseGps())
      {
        enKeyboard = KBD_POSTENTER;

        LoadSlide(pszMessages);
        Clear();

        Show();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM) 
        SetupTimeGps();
      else
      {
        AddKeyRecord(EVE_GPS_MANUAL);
        CorrectTimeGps();
      }
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetGpsCorrect(void)
{ 
  static uchar bSecondPrev;

  if (enKeyboard == KBD_POSTENTER)
  {
    uchar bSecond = GetCurrTimeDate()->bSecond;
    if (bSecond != bSecondPrev)
    {
    	bSecondPrev = bSecond;
      Show();
    }
  } 
}
