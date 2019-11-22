/*------------------------------------------------------------------------------
log35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../time/rtc.h"
#include "action35.h"
#include "log35.h"



#define LOG35_SIZE      100

static uint             cwLog35;
static log35            mLog35[LOG35_SIZE];


#define COUNTER35_SIZE  10

static counter35        mCounter35[COUNTER35_SIZE];



void    InitLog35(void)
{
  cwLog35 = 0;
  memset(&mLog35, 0, sizeof(mLog35));

  memset(&mCounter35, 0, sizeof(mCounter35));
}


void    Log35(event35  enEvent, uint  wData)
{
  log35 log;
  log.tiNow = *GetCurrTimeDate();
  log.enEvent = enEvent;
  log.wData = wData;

  mLog35[cwLog35++ % LOG35_SIZE] = log;

  ASSERT(enEvent < COUNTER35_SIZE);
  mCounter35[enEvent].tiNow = log.tiNow;
  mCounter35[enEvent].wCounter++;
}



void    OutLog35(void)
{
  InitPushCRC();
  PushIntLtl(cwLog35);
  Push(&mLog35, sizeof(mLog35));
  Output(2+sizeof(mLog35));
}


void    OutCounter35(void)
{
  InitPushCRC();
  Push(&mCounter35, sizeof(mCounter35));
  Output(sizeof(mCounter35));
}
