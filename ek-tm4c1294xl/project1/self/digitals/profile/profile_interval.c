/*------------------------------------------------------------------------------
profile_interval.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "profile_interval.h"



bool                    boProfileInterval;
cache const             chProfileInterval = {PROFILE_INTERVAL, &boProfileInterval, sizeof(bool)};

uchar                   bProfileIntervalDirect;
cache const             chProfileIntervalDirect = {PROFILE_INTERVAL_DIRECT, &bProfileIntervalDirect, sizeof(uchar)};

uchar                   bProfileIntervalModem;
cache const             chProfileIntervalModem = {PROFILE_INTERVAL_MODEM, &bProfileIntervalModem, sizeof(uchar)};



uchar                   ibProfileIntervalDig;



void    InitProfileInterval(void)
{
  LoadCacheBool(&chProfileInterval, true);
  LoadCacheChar(&chProfileIntervalDirect, 1, 250, 30);
  LoadCacheChar(&chProfileIntervalModem, 1, 250, 120);

  ibProfileIntervalDig = 0xFF;
}


void    ResetProfileInterval(void)
{
  SaveCacheBool(&chProfileInterval, true);
  SaveCacheChar(&chProfileIntervalDirect, 30);
  SaveCacheChar(&chProfileIntervalModem, 120);
}



uchar   GetProfileIntervalTimeout(void)
{
  return diCurr.ibPhone == 0 ? bProfileIntervalDirect : bProfileIntervalModem;
}


bool    IsFinishedProfileInterval(void)
{
  return ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= (uint)30*60 - GetProfileIntervalTimeout());
}



uchar   GetProfileIntervalDig(void)
{
  return ibProfileIntervalDig;
}


uchar   GetAndResetProfileIntervalDig(void)
{
  uchar c = ibProfileIntervalDig;
  ibProfileIntervalDig = 0xFF;
  return c;
}


void    SetProfileIntervalDig(uchar  c)
{
  ibProfileIntervalDig = c;
}



void    ShowProfileIntervalDigitalMesage(void)
{
  ShowLo(" приостановка...");
  DelayMsg();
}


void    ShowProfileIntervalBeforeMesage(void)
{
  ShowHi(" ќпрос профилей ");
  ShowLo("будет продолжен ");
  DelayMsg();

  ShowHi(" после перехода ");
  ShowLo(" через получас  ");
  DelayMsg();
}


void    ShowProfileIntervalAfterMesage(void)
{
  ShowHi("  ѕродолжение   ");
  ShowLo("опроса профилей ");
  DelayMsg();

  ShowHi(" после перехода ");
  ShowLo(" через получас  ");
  DelayMsg();
}
