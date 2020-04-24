/*------------------------------------------------------------------------------
extended_4t_36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../automatic1.h"
#include "io36.h"
#include "device36.h"
#include "automatic36.h"
#include "extended_4t_36.h"



status   ReadEnergyMonTariff36_Full(time  ti, uchar  ibTariff, uchar  bMaxLines)
{
  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      QueryEngMon36(i,ti);

      if (Input36() == SER_GOODCHECK) break;
      if (fKey == true) return ST_BADDIGITAL;

      if (IndexInBuff() == 3) return ST_NOTPRESENTED;
    }

    if (r == MaxRepeats()) return ST_BADDIGITAL;
    ShowPercent(70+i);

    ReadEngTariff36(i,ibTariff);
  }

  return ST_OK;
}



status  ReadCntMonCanTariff36(uchar  ibMonth, uchar  ibTariff, uchar  bMaxLines) // на начало мес€ца
{
  time2 ti2 = ReadTimeCan36();
  if (ti2.fValid == 0) return ST_BADDIGITAL;

  time ti = ti2.tiValue;
  if (ibMonth == 0)
  {
    ti.bMonth = 12;
    ti.bYear--;
  }
  else
  {
    if (ibMonth+1 > ti.bMonth) ti.bYear--;
    ti.bMonth = ibMonth;
  }

  status st = ReadEnergyMonTariff36_Full(ti,ibTariff,bMaxLines);

  if (st == ST_NOTPRESENTED)
  {
    Clear();
    sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
    Delay(1000);
    return(ST_NOTPRESENTED);
  }

  if (st != ST_OK) return st;


  QueryClose36();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

