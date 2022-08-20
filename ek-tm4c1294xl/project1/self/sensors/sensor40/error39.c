/*------------------------------------------------------------------------------
error39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "log40.h"
#include "error39.h"



uchar   Error39(uchar  bError) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
#endif  

  Log40(bError, 0);
  return bError;        
}


uchar   ErrorData39(uchar  bError, uint  wData) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
  MonitorString(" data="); MonitorIntDec(wData);
#endif  

  Log40(bError, wData);
  return bError;        
}
