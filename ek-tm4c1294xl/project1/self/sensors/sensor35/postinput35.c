/*------------------------------------------------------------------------------
POSTINPUT35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
//#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
#include "../../serial/input_wrapper.h"
//#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_status.h"
//#include "../../digitals/wait_answer.h"
#include "include35.h"
//#include "unpack35.h"
//#include "device35.h"
//#include "automatic35.h"
#include "io35.h"
//#include "timer35.h"
//#include "timeout35.h"
//#include "status35.h"
#include "action35.h"
#include "postinput35.h"



#ifndef SKIP_35

void    PostInput35(void)
{
  action35 action = Action35(true);
  if (action == A35_WAIT)
  {
    cbRepeat = MaxRepeats();
    Query35Internal(250, 0, NNCL2_DATA_GET);
    SetCurr(DEV_DATAGET_35);
  }
  else if (action == A35_SUCCESS)
  {
    InputGoodCheck();
    mpSerial[ibPort] = SER_GOODCHECK;
  }
  else if (action == A35_ERROR)
  {
    mpSerial[ibPort] = SER_BADCHECK;
  }
  else
  {
    ASSERT(false);
  }
}

#endif
