/*------------------------------------------------------------------------------
error40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "log40.h"
#include "error40.h"



uchar   Error40(uchar  bError) {
#ifdef  MONITOR_40  
  MonitorString("\n error="); MonitorCharDec(bError);
#endif  

  Log40(bError, 0);
  return bError;        
}


uchar   ErrorData40(uchar  bError, uint  wData) {
#ifdef  MONITOR_40  
  MonitorString("\n error="); MonitorCharDec(bError);
  MonitorString(" data="); MonitorIntDec(wData);
#endif  

  Log40(bError, wData);
  return bError;        
}
