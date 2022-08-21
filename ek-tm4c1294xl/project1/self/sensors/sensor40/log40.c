/*------------------------------------------------------------------------------
log40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../time/rtc.h"
#include "log40_include.h"
#include "log40.h"



static uint             cwLog40;
static log40            mLog40[LOG40_SIZE];


static counter40        mCounter40[COUNTER40_SIZE];



void    InitLog40(void)
{
  cwLog40 = 0;
  memset(&mLog40, 0, sizeof(mLog40));

  memset(&mCounter40, 0, sizeof(mCounter40));
}


void    Log40(uchar  bError, uint  wData)
{
  log40 log;
  log.tiNow = *GetCurrTimeDate();
  log.bError = bError;
  log.wData = wData;

  mLog40[cwLog40++ % LOG40_SIZE] = log;

  if (bError < COUNTER40_SIZE)
  {
    mCounter40[bError].tiNow = log.tiNow;
    mCounter40[bError].wCounter++;
  }
}



void    OutLog40(void)
{
  InitPushCRC();

  uint wSize = 0;
  wSize += PushIntLtl(cwLog40);

  uint i;
  for (i=0; i<LOG40_SIZE; i++)
  {
    log40 log = mLog40[i];
    wSize += PushTime(log.tiNow);
    wSize += PushChar(log.bError);
    wSize += PushIntLtl(log.wData);
  }

  Output(wSize);
}


void    OutCounter40(void)
{
  InitPushCRC();

  uint wSize = 0;

  uint i;
  for (i=0; i<COUNTER40_SIZE; i++)
  {
    counter40 cnt = mCounter40[i];
    wSize += PushTime(cnt.tiNow);
    wSize += PushIntLtl(cnt.wCounter);
  }

  Output(wSize);
}


void    OutResetLog40(void)
{
  InitLog40();
  Result(bRES_OK);
}
