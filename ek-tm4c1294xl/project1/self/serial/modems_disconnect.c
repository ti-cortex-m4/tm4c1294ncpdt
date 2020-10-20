/*------------------------------------------------------------------------------
modems_disconnect.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../devices/devices.h"
#include "../devices/devices_init.h"
#include "monitor.h"
#include "modems_disconnect.h"



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
    MonitorString("\n disconnect: no connection - no disconnect");
    return false;
  }
  else
  {
    if (boModemDisconnectBetweenDigitals)
    {
      MonitorString("\n disconnect: by default - disconnect");
      return true;
    }
    else {
      uchar c = GetNextDigitalIdx();
      if (c == 0xFF) {
        MonitorString("\n disconnect: connection, the last digital - disconnect");
        return true;
      }

      if( (GetDigitalPort(ibDig)  == GetDigitalPort(c))    &&
          (GetDigitalPhone(ibDig) == GetDigitalPhone(c)) ) {
        MonitorString("\n disconnect: connection, the same port/phone - no disconnect");
        return false;
      } else {
        MonitorString("\n disconnect: connection, another port/phone - disconnect");
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
    MonitorString("\n connection: by default "); MonitorBool(boConnect);
    return boConnect;
  }
  else
  {
    bool boConnect = ((fConnect == 0) && (diCurr.ibPhone != 0));
    MonitorString("\n connection: "); MonitorBool(fConnect == 0); MonitorBool(diCurr.ibPhone != 0); MonitorBool(boConnect);
    return boConnect;
  }
}
