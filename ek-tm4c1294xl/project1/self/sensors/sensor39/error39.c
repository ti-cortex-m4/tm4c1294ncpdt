/*------------------------------------------------------------------------------
error39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../time/rtc.h"
#include "include39.h"
#include "error39.h"



typedef struct
{
  time          tiNow;
  uchar         bError;
  uint          wData;
} log39;


typedef struct
{
  time          tiNow;
  uint          wCounter;
} counter39;



#define LOG39_SIZE      100

static uint             cwLog39;
static log39            mLog39[LOG39_SIZE];



#define COUNTER39_SIZE  0x100

static counter39        mCounter39[COUNTER39_SIZE];



void    InitLog39(void)
{
  cwLog39 = 0;
  memset(&mLog39, 0, sizeof(mLog39));

  memset(&mCounter39, 0, sizeof(mCounter39));
}


void    Log39(uchar  bError, uint  wData)
{
  log39 log;
  log.tiNow = *GetCurrTimeDate();
  log.bError = bError;
  log.wData = wData;

  mLog39[cwLog39++ % LOG39_SIZE] = log;

  ASSERT(bError < COUNTER39_SIZE);

  mCounter39[bError].tiNow = log.tiNow;
  mCounter39[bError].wCounter++;
}



void    OutLog39(void)
{
  InitPushCRC();
  PushIntLtl(cwLog39);
  Push(&mLog39, sizeof(mLog39));
  Output(2+sizeof(mLog39));
}


void    OutCounter39(void)
{
  InitPushCRC();
  Push(&mCounter39, sizeof(mCounter39));
  Output(sizeof(mCounter39));
}



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
