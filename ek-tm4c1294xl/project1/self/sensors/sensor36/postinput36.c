/*------------------------------------------------------------------------------
postinput36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/digitals_pause.h"
#include "include36.h"
#include "io36.h"
#include "../sensor35/status35.h"
#include "action36.h"
#include "postinput36.h"



bool    IgnoreChecksumError36(void)
{
  if (GetCurr35Internal() == DEV_OPENCANAL_36C)
    return true;

  if (GetCurr35Internal() == DEV_OPENCANAL_36P)
    return true;

  return false;
}



void    PostInput36(void)
{
  action35 action = Action36(true, IgnoreChecksumError36());
  if (action == A35_WAIT)
  {
    MonitorString("\t postinput: wait");
    SetCurr(DEV_RUN_WAIT_35);
  }
  else if (action == A35_SUCCESS)
  {
    MonitorString("\t postinput: success");
    InputGoodCheck();
    mpSerial[ibPort] = SER_GOODCHECK;
  }
  else if (action == A35_ERROR)
  {
    MonitorString("\t postinput: error");
    mpSerial[ibPort] = SER_BADCHECK;
  }
  else if (action == A35_BREAK)
  {
    MonitorString("\t postinput: run break");
    mpSerial[ibPort] = SER_BADCHECK;
    SetCurr(DEV_RUN_BREAK_35);
  }
  else
  {
    ASSERT(false);
  }
}
