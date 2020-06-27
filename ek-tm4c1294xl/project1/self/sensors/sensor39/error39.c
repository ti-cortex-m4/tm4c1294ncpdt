/*------------------------------------------------------------------------------
error39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "log39.h"
#include "error39.h"



uchar   Error39(uchar  bError) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
#endif  
//  Log39(bError, 0);
  return bError;        
}


uchar   Error39_(uchar  bError, uint  wCode) {
#ifdef  MONITOR_39  
  MonitorString("\n error="); MonitorCharDec(bError);
  MonitorString("\n code="); MonitorIntDec(wCode);
#endif  
//  Log39(bError, wCode);
  return bError;        
}
