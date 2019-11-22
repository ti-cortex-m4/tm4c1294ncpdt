/*------------------------------------------------------------------------------
log35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "log35.h"



#define LOG35_SIZE      100

static uint             cwLog35;
static log35            mLog35[LOG35_SIZE];


#define COUNTER35_SIZE  10

static counter35        mCounter35[COUNTER35_SIZE];



void    InitLog35(void)
{
  cwLog35 = 0;
  memset(&mbLog35, 0, sizeof(mbLog35));

  memset(&mCounter35, 0, sizeof(mCounter35));
}


void    Log35(action35  enAction, uint  wData)
{
  log35 log;
  log.tiNow = current time;
  log.enAction = enAction;
  log.wData = wData;

  mbLog35[cwLog35++ % LOG35_SIZE] = log;

  assert(enAction < COUNTER35_SIZE);
  mCounter35[enAction].tiNow = log.tiNow;
  mCounter35[enAction].wCounter++;
}



void    OutLog35(void)
{
  InitPushCRC();
  PushIntLtl(cwLog35);
  Push(&mbLog35, sizeof(mbLog35));
  Output(2+sizeof(mbLog35));
}


void    OutCounter35(void)
{
  InitPushCRC();
  Push(&mCounter35, sizeof(mCounter35));
  Output(sizeof(mCounter35));
}
