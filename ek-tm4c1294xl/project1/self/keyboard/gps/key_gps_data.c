/*------------------------------------------------------------------------------
KEY_GPS_DATA.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"
#include "../../time/timedate_display.h"



static void Show(uchar  ibX)
{
  Clear();

  switch (ibX)
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
      switch (ibX)
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
static uchar ibX;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if ((bPortGps > 0) && (bPortGps <= bPORTS))
      {
        enKeyboard = KBD_POSTENTER;

        ibX = 0;
        Show(ibX);
      }
      else BlockProgram(bSET_GPS_CONFIG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 4) ibX = 0;
      Show(ibX);
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetGpsData(void)
{/*
  if (enKeyboard == KBD_POSTENTER)
  {
    ibY = (*PGetCurrTimeDate()).bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;
      ShowGpsData();
    }
  }*/
}
