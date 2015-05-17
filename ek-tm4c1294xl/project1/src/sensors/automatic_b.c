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
    if (fKey == 1) return(0);

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return(0);

  return(1);
}



bool    QueryOpenB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  return(1);
}



bool    QueryTimeAltB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadTimeAltB();
  return(1);
}



bool    QueryEnergyB_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyB();
  return(1);
}



bool    QueryEnergyB_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    if (QueryIdB_Full() == 0) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyB();
  return(1);
}



void    QueryCounterMonTariffB(uchar  ibMonth, uchar  bTariff) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(6);
  PushChar(2);

  uint i = 0x2BB + 0x55*ibMonth + 0x11*bTariff;
  PushChar(i / 0x100);
  PushChar(i % 0x100);
  PushChar(16);

  QueryIO(1+16+2, 3+3+2);
}


bool    QueryCounterMonTariffB_Full(uchar  ibMonth, uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCounterMonTariffB(ibMonth, bTariff);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyB();
  return(1);
}


status ReadCntMonCanTariffB(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceB() == 0) return(ST4_BADDIGITAL);

  if (QueryCounterMonTariffB_Full(ibMonth, ibTariff) == 0) return(ST4_BADDIGITAL);  

  ShowPercent(60+ibTariff);
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
