/*------------------------------------------------------------------------------
KEY_GPS_CORRECT.C


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
#include        "nexttime.h"
#include        "gps.h"
#include        "record.h"



//                                         0123456789ABCDEF
message         code    szCorrectGPS     = "Коррекция GPS   ";



void    ShowGPSCorrect(void)
{
  if (ReadTimeDateGPS() == 0)
  {
    Error(); 
    DelayInf(); Clear();
  }
  else
  {
    if (ShowStatusGPS() == 1)
      ShowDeltaTime();
  }
}


void    key_GetGPSCorrect(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if ((bPortGPS > 0) && (bPortGPS <= bPORTS))
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szCorrectGPS);
        Clear();

        ShowGPSCorrect();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM) 
        SetupTimeGPS();
      else
      {
        AddKeyRecord(EVE_GPS_MANUAL);
        CorrectTimeGPS();
      }
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetGPSCorrect(void)
{ 
  if (enKeyboard == KBD_POSTENTER)
  {
    ibY = (*PGetCurrTimeDate()).bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;
      ShowGPSCorrect();
    }
  } 
}

*/
