/*------------------------------------------------------------------------------
IO36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
//#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/input_wrapper.h"
//#include "../../serial/monitor.h"
//#include "../../digitals/wait_answer.h"
//#include "include35.h"
//#include "pack35.h"
//#include "router35.h"
//#include "device35.h"
//#include "action35.h"
//#include "timer35.h"
//#include "log35.h"
#include "io36.h"



void    Query36(uchar  cbIn, uchar  cbOut)
{
}


serial  Input36(void)
{
  return mpSerial[ibPort];
}
