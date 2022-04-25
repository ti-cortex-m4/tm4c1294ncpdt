/*------------------------------------------------------------------------------
AUTOMATIC19.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "device19.h"
#include "automatic19.h"



#ifndef SKIP_N

bool    AutomaticN(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(0);
    PushChar(diCurr.bAddress);

    PushChar(8);

    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);

    QueryIO(5+8, 5+8);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);

  sprintf(szLo+1,"версия:");
  szLo[ 9] = InBuff(3);
  szLo[10] = InBuff(4);
  szLo[11] = InBuff(5);
  szLo[12] = InBuff(6);
  szLo[13] = InBuff(7);

  DelayInf(); Clear();


  for (i=0; i<MaxRepeats(); i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);

  ReadEnergyN();

  mpdwBase[ibDig] = mpdwChannelsA[0];

  return(1);
}


// чтение реальных показаний счётчиков для преобразователей ПИ-1.4
bool    ReadSensorN(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyN();


  reBuffA = *PGetCanLong(mpdwChannelsA, 0) * *PGetCanReal(mpreValueCntHou,ibDig);
  reBuffA += *PGetCanReal(mpreCount,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif
