/*------------------------------------------------------------------------------
modems_disconnect.c


------------------------------------------------------------------------------*/

#include    "../main.h"
//#include    "../memory/mem_ports.h"
//#include    "../memory/mem_digitals.h"
//#include    "../memory/mem_phones.h"
//#include    "../display/display.h"
//#include    "../keyboard/keyboard.h"
//#include    "../keyboard/time/key_timedate.h"
//#include    "../time/delay.h"
//#include    "../flash/records.h"
//#include    "../devices/devices_init.h"
#include    "../digitals/digitals.h"
//#include    "../digitals/digitals_pause.h"
#include    "../devices/devices.h"
//#include    "../digitals/digitals_messages.h"
//#include    "../digitals/digitals_display.h"
//#include    "ports.h"
//#include    "ports_common.h"
//#include    "ports_devices.h"
//#include    "ports_modems.h"
//#include    "speeds_display.h"
//#include    "flow.h"
#include    "monitor.h"
#include    "modems_disconnect.h"



uchar   GetNextDigitalIdx()
{
  uchar c;
  for (c=ibDig; c<bCANALS; c++)
  {
    MonitorString("\n c="); MonitorIntDec(c);
    if (CompareLines(ibDig,c) == true)
    {
      MonitorString("\n the same digital, skip");
      continue;
    } else {
      MonitorString("\n the next digital");
      return c;
    }
  }

  MonitorString("\n no next digital");
  return 0xFF;
}


bool    IsModemDisconnect(void)
{
  bool fConnected = (diCurr.ibPhone != 0) && (fConnect == 1); // есть соединение ?

  if (!fConnected)
  {
    MonitorString("\n no connection - no disconnect");
    return false;
  }
  else
  {
    if (boModemDisconnectBetweenDigitals)
    {
      return true;
    }
    else {
      uchar c = GetNextDigitalIdx();
      if (c == 0xFF) {
        MonitorString("\n connection, the last digital - disconnect");
        return true;
      }

      if( (GetDigitalPort(ibDig)  == GetDigitalPort(c))    &&
              (GetDigitalPhone(ibDig) == GetDigitalPhone(c)) ) {
        MonitorString("\n connection, the same port/phone - no disconnect");
        return false;
      } else {
        MonitorString("\n connection, another port/phone - disconnect");
        return true;
      }
    }
  }
}

