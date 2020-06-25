/*------------------------------------------------------------------------------
DEVICE36*C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "include39.h"
//#include "crc16x25.h"
//#include "io39.h"
//#include "hdlc_address.h"
//#include "dlms_push.h"
#include "caller39.h"



caller39 InitCaller(void)
{
  caller39 runner;

  runner.bNS = 0;
  runner.bNR = 0;
  runner.bInvokeId = 0;

  return runner;
}
