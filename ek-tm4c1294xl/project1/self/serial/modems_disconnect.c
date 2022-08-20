/*------------------------------------------------------------------------------
modems_disconnect.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../devices/devices.h"
#include "../devices/devices_init.h"
#include "monitor.h"
#include "modems_disconnect.h"



static bool             boSamePhone;



uchar   GetNextDigitalIdx()
{
  uchar c;
  for (c=ibDig; c<bCANALS; c++)
  {
#ifdef MONITOR_MODEM_DISCONNECT
    MonitorString("\n c="); MonitorIntDec(c);
#endif
    if (CompareLines(ibDig,c) == true)
    {
#ifdef MONITOR_MODEM_DISCONNECT
      MonitorString("\n the same digital, skip");
#endif
      continue;
    } else {
#ifdef MONITOR_MODEM_DISCONNECT
      MonitorString("\n the next digital");
#endif
      return c;
    }
  }

#ifdef MONITOR_MODEM_DISCONNECT
  MonitorString("\n no next digital");
#endif
  return 0xFF;
}


bool    IsModemDisconnect(void)
{
  boSamePhone = false;

  bool fConnected = (diCurr.ibPhone != 0) && (fConnect == 1); // есть соединение ?

  if (!fConnected)
  {
#ifdef MONITOR_MODEM_DISCONNECT
    MonitorString("\n disconnect: no connection - no disconnect");
#endif
    return false;
  }
  else
  {
    if (boModemDisconnectBetweenDigitals)
    {
#ifdef MONITOR_MODEM_DISCONNECT
      MonitorString("\n disconnect: by default - disconnect");
#endif
      return true;
    }
    else {
      uchar c = GetNextDigitalIdx();
      if (c == 0xFF) {
#ifdef MONITOR_MODEM_DISCONNECT
        MonitorString("\n disconnect: connection, the last digital - disconnect");
#endif
        return true;
      }

      if( (GetDigitalPort(ibDig)  == GetDigitalPort(c))    &&
          (GetDigitalPhone(ibDig) == GetDigitalPhone(c)) ) {
#ifdef MONITOR_MODEM_DISCONNECT
        MonitorString("\n disconnect: connection, the same port/phone - no disconnect");
#endif
        boSamePhone = true;
        return false;
      } else {
#ifdef MONITOR_MODEM_DISCONNECT
        MonitorString("\n disconnect: connection, another port/phone - disconnect");
#endif
        return true;
      }
    }
  }
}



bool    IsModemConnect(void)
{
  if (boModemDisconnectBetweenDigitals)
  {
    bool boConnect = (diCurr.ibPhone != 0);
#ifdef MONITOR_MODEM_DISCONNECT
    MonitorString("\n connection: by default "); MonitorBool(boConnect);
#endif
    return boConnect;
  }
  else
  {
    if (diCurr.ibPhone == 0)
    {
#ifdef MONITOR_MODEM_DISCONNECT
      MonitorString("\n connection: direct, no connect ");
#endif
      return false;
    }
    else
    {
      if (boSamePhone)
        fConnect = 1;

      bool boConnect = !boSamePhone;
#ifdef MONITOR_MODEM_DISCONNECT
      MonitorString("\n same phone: "); MonitorBool(boSamePhone);
      MonitorString("\n connection: "); MonitorBool(boConnect);
#endif
      return boConnect;
    }
  }
}
