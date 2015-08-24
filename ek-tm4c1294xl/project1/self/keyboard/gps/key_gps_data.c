/*------------------------------------------------------------------------------
KEY_GPS_DATA.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "display.h"
#include        "timedate.h"
#include        "beep.h"
#include        "delay.h"
#include        "ports.h"
#include        "rtc.h"
#include        "gps.h"



void    ShowGPSData_Error(void)
{
  Error(); DelayInf(); 
  Clear();
}


void    ShowGPSData_OK(void)
{
  if (ShowStatusGPS() == 1)
  {
    switch (ibX)
    {
      case 0: ShowTime();      break;
      case 1: ShowDeltaTime(); break;
      case 2: ShowTimeDate();  break;
      case 3: sprintf(szLo+7,"%bu.%bu",bVersionMaxGPS,bVersionMinGPS); break;
    }
  } 
}


void    ShowGPSData(void)
{
  switch (ibX)
  {
    case 0: ShowHi(szTimeGPS);      break;
    case 1: ShowHi(szDeltaTimeGPS); break;
    case 2: ShowHi(szTimeDateGPS);  break;
    case 3: ShowHi(szVersionGPS);   break;
  }

  switch (ReadTimeDateGPS())
  {
    case 0: ShowGPSData_Error(); break;
    case 1: ShowGPSData_OK();    break;
  }
}


void    key_GetGPSData(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if ((bPortGPS > 0) && (bPortGPS <= bPORTS))
      {
        enKeyboard = KBD_POSTENTER;

        ibX = 0; ibXmax = 4;
        Clear(); ShowGPSData();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= ibXmax) ibX = 0;
      Clear(); ShowGPSData();
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetGPSData(void)
{ 
  if (enKeyboard == KBD_POSTENTER)
  {
    ibY = (*PGetCurrTimeDate()).bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;
      ShowGPSData();
    }
  } 
}
*/
