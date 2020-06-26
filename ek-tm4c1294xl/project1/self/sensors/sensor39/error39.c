/*------------------------------------------------------------------------------
error39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "error39.h"



uchar   Error39(uchar  bError) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
#endif  
  return bError;        
}


uchar   Error39_(uchar  bError, uint  wCode) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
  MonitorString("\n code="); MonitorIntDec(wCode);
#endif  
  return bError;        
}


uchar   Log39(uchar  bLog) {
  return bLog;        
}
