/*------------------------------------------------------------------------------
KEY_GPS_DATA,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"
#include "../../time/rtc.h"
#include "../../time/timedate_display.h"



static uchar            ibVal;



static void Show(uchar  ibVal)
{
  switch (ibVal)
  {
    case 0: ShowHi(szTimeGps); break;
    case 1: ShowHi(szDeltaTimeGps); break;
    case 2: ShowHi(szTimeDateGps); break;
    case 3: ShowHi(szVersionGps); break;
  }

  time2 tm2 = ReadTimeDateGps();
  if (tm2.fValid == false)
  {
    Error(); DelayInf(); Clear();
  }
  else
  {
    if (ShowStatusGps() == 1)
    {
      switch (ibVal)
      {
        case 0: ShowTime(tm2.tiValue); break;
        case 1: ShowDeltaTime(tm2.tiValue); break;
        case 2: ShowTimeDate(tm2.tiValue); break;
        case 3: sprintf(szLo+7,"%u.%u",bVersionMaxGps,bVersionMinGps); break;
      }
    }
  }
}


void    key_GetGpsData(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UseGps())
      {
        enKeyboard = KBD_POSTENTER;

        ibVal = 0;
        Clear(); Show(ibVal);
      }
      else BlockProgram(bSET_GPS_CONFIG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibVal >= 4) ibVal = 0;
      Clear(); Show(ibVal);
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetGpsData(void)
{
static uchar bSecondPrev;

  if (enKeyboard == KBD_POSTENTER)
  {
    uchar bSecond = GetCurrTimeDate()->bSecond;
    if (bSecond != bSecondPrev)
    {
      bSecondPrev = bSecond;
      Show(ibVal);
    }
  }
}
