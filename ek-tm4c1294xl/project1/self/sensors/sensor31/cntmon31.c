/*------------------------------------------------------------------------------
CNTMON31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../display/display.h"
//#include "../../time/timedate.h"
//#include "../../time/delay.h"
//#include "../../devices/devices.h"
//#include "../../digitals/current/current_run.h"
//#include "../../digitals/digitals_messages.h"
//#include "automatic31.h"
#include "cntmon31.h"



#ifndef SKIP_N31

bool    ReadCntMonCan31(uchar  ibMonth)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceG() == 0) return(0);
  reBuffX = reBuffB;


  DelayOff();
  QueryTimeG();

  if (CodInput() != SER_GOODCHECK) return(0);  if (fKey == 1) return(0);
  ShowPercent(55);

  ReadTimeAltG();


  for (i=0; i<30; i++) mpreCodEng30[i] = 0;

  if (ExtVersionCod())
  {
    if (tiAlt.bMonth != ibMonth+1)
    {
      if (bVersionCod == 49)
        return ReadCntMonCanExt_G(ibMonth);
      else
        { sprintf(szLo,"   необходима   "); Delay(1000); sprintf(szLo,"   верси€ 49    "); Delay(1000); return(0); }
    }
    else                                        // значени€е счЄтчиков на начало текущего мес€ца
    {
      if (ReadEnergyExt_G() == 0) return(0);
    }
  }
  else
  {
    if (tiAlt.bMonth != ibMonth+1)
    {
      { sprintf(szLo,"   необходима   "); Delay(1000); sprintf(szLo,"   верси€ 49    "); Delay(1000); return(0); }
    }
    else                                        // значени€е счЄтчиков на начало текущего мес€ца
    {
      if (ReadEnergyBCD_G() == 0) return(0);
    }
  }

  ShowPercent(100);


  for (i=0; i<6; i++)
  {
    mpreChannelsB[i] = mpreCodEng30[i*5+0] - mpreCodEng30[i*5+3];

    reBuffA = *PGetCanReal(mpreChannelsB, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;
  }

  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif
