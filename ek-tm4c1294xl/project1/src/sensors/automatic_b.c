/*------------------------------------------------------------------------------
AUTOMATIC_B.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../digitals/digitals_messages.h"
#include "../engine.h"
#include "automatic1.h"
#include "device_b.h"



bool    QueryIdB_Full(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryIdB();

    if ((Input() == SER_GOODCHECK) && (ReadIdB() == 1)) break;
    if (fKey == 1) return false;

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return false;

  return true;
}



bool    QueryOpenB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  return true;
}



bool    QueryTimeAltB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadTimeAltB();
  return true;
}



bool    QueryEnergyB_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}



bool    QueryEnergyB_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return false;

    if (QueryIdB_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}



static void QueryCntMonTariffB(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  PushChar(2);

  uint w = 0x2BB + 0x55*ibMon + 0x11*bTrf;
  PushChar(w / 0x100);
  PushChar(w % 0x100);
  PushChar(16);

  QueryIO(1+16+2, 3+3+2);
}


static bool QueryCounterMonTariffB_Full(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCntMonTariffB(ibMon, bTrf);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyB();
  return true;
}


status ReadCntMonCanTariffB(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceB() == 0) return(ST4_BADDIGITAL);

  if (QueryCounterMonTariffB_Full(ibMon, ibTrf) == 0) return(ST4_BADDIGITAL);  

  ShowPercent(60+ibTrf);
  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  reKtrans = reKtrans/reBuffA;

  for (i=0; i<4; i++) 
  {
    mpreChannelsB[i] = mpdwChannelsB[i] * reKtrans;
    mpboChannelsA[i] = TRUE;
  }

  return(ST4_OK);
}
