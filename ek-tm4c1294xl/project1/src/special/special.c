/*------------------------------------------------------------------------------
SPECIAL.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_energy_spec.h"
#include        "../display/display.h"
#include        "../tariffs/tariffs.h"
#include        "../impulses/energy_spec.h"
#include        "../devices/devices.h"
#include        "../devices/extended_5.h"
#include        "../devices/extended_7.h"
#include        "../time/delay.h"
#include        "../time/timedate.h"
#include        "../time/decret.h"
#include        "../energy.h"
#include        "../energy3.h"
#include        "calc.h"
#include        "special.h"



//                                          0123456789ABCDEF
static char const       szSpecialBegin[] = " подготовка...  ",
                        szSpecialEnd[]   = " завершение...  ";



bool    IsDefect(uchar  ibCan)
{
  LoadImpHouSpec(iwDigHou,1);
  return(GetCanInt(mpwImpHouCanSpec, ibCan) == 0xFFFF);
}


bool    IsWinterDouble(uchar  ibCan)
{
  return(IsWinter(&tiAlt) && (mpbWinterCan[ibCan] < 2));
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


void    MakeSpecial(void)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",tiAlt.bHour,tiAlt.bMinute);

    CalcTimeDate(1,1);


    MakeAllPrevTariffs();

    CalcDigCanals();

    fLoadMem = 0;
    CalcAllGroups(1);
  }
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

  CloseExtended5();
  CloseExtended7();
}
