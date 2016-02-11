/*------------------------------------------------------------------------------
SPECIAL!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_energy_spec.h"
#include "../display/display.h"
#include "../tariffs/tariffs.h"
#include "../impulses/energy_spec.h"
#include "../devices/devices.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../time/decret.h"
#include "../energy.h"
#include "../kernel/arrays_buff.h"
#include "calc.h"
#include "special.h"



//                                          0123456789ABCDEF
static char const       szSpecialBegin[] = " подготовка...  ",
                        szSpecialEnd[]   = " завершение...  ";



bool    IsDefect(uchar  ibCan)
{
  LoadImpHouSpec(iwDigHou,1);
  return mpwImpHouCanSpec[ibCan] == 0xFFFF;
}


bool    IsWinterDouble(uchar  ibCan, time  ti)
{
  return(IsWinter(ti) && (mpbWinterCan[ibCan] < 2));
}



bool    IsOpenSpecial(void)
{
  return(fLoadDay || fLoadMon);
}


void    OpenSpecial(void)
{
  ShowLo(szSpecialBegin);
  DelayInf(); Clear();

  OpenCalc();
}


bool    MakeSpecial(time  ti)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig, ti))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",ti.bHour,ti.bMinute);

    CalcTimeDate(1, 1, ti);


    MakeAllPrevTariffs(ti);

    CalcDigCanals(ti);

    fLoadMem = 0;
    CalcAllGroups(1, ti);

    return true;
  }

  return false;
}


void    CloseSpecial(void)
{
  ShowLo(szSpecialEnd);
  DelayInf(); Clear();

  CloseCalc(1,1);
}


// TODO CloseSpecialBuff - add flags
void    CloseSpecialBuff(void)
{
  SaveImpHouBuff();

  SaveImpDayBuff();
  SaveImpMonBuff();

  SavePowDayBuff();
  SavePowMonBuff();
}
